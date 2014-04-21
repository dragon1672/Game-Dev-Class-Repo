using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace CSharpOBJConverter
{
	class Program
	{
		private readonly LineParse<Vec3> _posParser;
		private readonly LineParse<Vec3> _normParser;
		private readonly LineParse<Vec2> _uvsParser;
		private readonly LineParse<IndiceeSet> _verParser;
		private readonly List<Vertex> _allVerts;
		private readonly List<Vec3> _allIndicees;

		public Program()
		{
			_posParser = new LineParse<Vec3>("v");
			_normParser = new LineParse<Vec3>("vn");
			_uvsParser = new LineParse<Vec2>("vt");
			_verParser = new LineParse<IndiceeSet>("f", AddVerts);
			_allVerts = new List<Vertex>();
			_allIndicees = new List<Vec3>();
		}

		private void AddVerts(IndiceeSet toAdd)
		{
			Vec3 indexs = new Vec3
			{
				X = _allVerts.IndexOf(toAdd.One),
				Y = _allVerts.IndexOf(toAdd.Two),
				Z = _allVerts.IndexOf(toAdd.Thr)
			};
			if (indexs.X < 0)
			{
				indexs.X = _allVerts.Count;
				_allVerts.Add(toAdd.One);
			}
			if (indexs.Y < 0)
			{
				indexs.Y = _allVerts.Count;
				_allVerts.Add(toAdd.Two);
			}
			if (indexs.Z < 0)
			{
				indexs.Z = _allVerts.Count;
				_allVerts.Add(toAdd.Thr);
			}
			_allIndicees.Add(indexs);
		}

		private void PopulateVertexs()
		{
			foreach(var item in _allVerts)
			{
				item.Position = (item.NPosition < 0) ? new Vec3(0, 0, 0) : _posParser.ParsedData[item.NPosition];
				item.Uv = (item.NUv < 0) ? new Vec2(0, 0) : _uvsParser.ParsedData[item.NUv];
				item.Normal = (item.NNormal < 0) ? new Vec3(0, 0, 0) : _normParser.ParsedData[item.NNormal];
			}
		}

		public void LoadFile(string filepath, int veboseLevel=0)
		{
			StreamReader fileReader = new StreamReader(filepath);
			string line;
			var rawParse = new List<ILineParser>();
			rawParse.Add(_posParser);
			rawParse.Add(_normParser);
			rawParse.Add(_uvsParser);
			rawParse.Add(_verParser);
			//parse all data
			while ((line = fileReader.ReadLine()) != null)
			{
				bool added = false;
				foreach (var currParse in rawParse)
				{
					added = currParse.IsLine(line);
					if (!added) continue;
					currParse.AddData(line);
					break;
				}
				if(veboseLevel>1 && !added) Console.WriteLine("Discarding: " + line);
			}
			if(veboseLevel>0) Console.WriteLine("File Parsed");
			PopulateVertexs();
			fileReader.Close();
		}
		/// <summary>
		/// Writes currently loaded OBJ file to binary file
		/// the 1st int is the vertex Offset
		/// the 2nd int is the number of vertexs
		/// the 3rd int is the indice Offset
		/// the 3th int is the number of indicees
		/// </summary>
		/// <param name="filepath">file to be written to</param>
		/// <param name="defaulExtension">if no extension if speficied then this will be apended to the filename</param>
		public void WriteBinFile(string filepath, string defaulExtension=".bin")
		{
			if (!filepath.Contains('.')) filepath += defaulExtension;
			BinaryWriter outFile =
				new BinaryWriter(File.Open(filepath, File.Exists(filepath) ? FileMode.Truncate : FileMode.CreateNew));
			int vertexOffset = 0;
			int vertexSize = _allVerts.Count * (sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 3); // 3F pos, 2F UV, 3F norm
			int indiceOffset = vertexSize;
			int indiceSize = _allIndicees.Count * (sizeof(ushort) * 3); // 3 floats for each segment
			outFile.Write(vertexOffset);
			outFile.Write(vertexSize);
			outFile.Write(indiceOffset);
			outFile.Write(indiceSize);
			foreach (var allVert in _allVerts)
				WriteVertex(outFile, allVert);

			foreach (var allIndicee in _allIndicees)
				WriteIndicee(outFile, allIndicee);
			outFile.Close();
		}

		private static void WriteIndicee(BinaryWriter outFile, Vec3 toWrite)
		{
			outFile.Write((ushort)toWrite.X);
			outFile.Write((ushort)toWrite.Y);
			outFile.Write((ushort)toWrite.Z);
		}

		private static void WriteVec3(BinaryWriter outFile, Vec3 toWrite)
		{
			outFile.Write(toWrite.X);
			outFile.Write(toWrite.Y);
			outFile.Write(toWrite.Z);
		}
		private static void WriteVec2(BinaryWriter outFile, Vec2 toWrite)
		{
			outFile.Write(toWrite.X);
			outFile.Write(toWrite.Y);
		}
		private static void WriteVertex(BinaryWriter outFile, Vertex toWrite)
		{
			WriteVec3(outFile, toWrite.Position);
			WriteVec2(outFile, toWrite.Uv);
			WriteVec3(outFile, toWrite.Normal);
		}

		public void PrintBinFile(string filePath)
		{
			BinaryReader file = new BinaryReader(File.Open(filePath,FileMode.Open));
			Console.WriteLine();
			int vertexOffset = file.ReadInt32();
			int vertexSize = file.ReadInt32();
			int indiceOffset = file.ReadInt32();
			int indiceSize = file.ReadInt32();
			int numOfVerts = vertexSize / (sizeof(float) * 3 + sizeof(float) * 2 + sizeof(float) * 3); // 3F pos, 2F UV, 3F norm
			int numOfindices = indiceSize/(sizeof (ushort)*3);
			Console.WriteLine("vertexOffset: " + vertexOffset);
			Console.WriteLine("vertexSize: " + vertexSize);
			Console.WriteLine("indiceOffset: " + indiceOffset);
			Console.WriteLine("indiceSize: " + indiceSize);
			Console.WriteLine("Num of verts: " + numOfVerts);
			Console.WriteLine("Num of indices: " + numOfindices);
			for (int i = 0; i < numOfVerts; i++)
			{
				Vertex toPrint = new Vertex(0, 0, 0);
				toPrint.Position = new Vec3(file.ReadSingle(), file.ReadSingle(), file.ReadSingle());
				toPrint.Uv = new Vec2(file.ReadSingle(), file.ReadSingle());
				toPrint.Normal = new Vec3(file.ReadSingle(), file.ReadSingle(), file.ReadSingle());
				Console.WriteLine(i+": "+toPrint);
			}
			for (int i = 0; i < numOfindices; i++)
			{
				ushort one = (ushort)file.ReadInt16();
				ushort two = (ushort)file.ReadInt16();
				ushort thr = (ushort)file.ReadInt16();
				Console.WriteLine("Indicee: { " + one + ", " + two + ", " + thr + " }");
			}
			file.Close();
		}

		static void Main(string[] args)
		{
			//* release
			if (args.Length > 0)
			{
				Program myProg = new Program();
				string inFile = args[0];
				int verbose = 0;
				string outFile = inFile.Substring(0, inFile.Length - 4) + ".bin";
				if (args.Length > 1)
				{
					if (args.Length > 2) {
						verbose = int.Parse(args[2]);
					} else {
						try {
							verbose = int.Parse(args[1]);
						} catch {
							verbose = 0;
							outFile = args[1];
						}
					}
				}
				myProg.LoadFile(inFile, verbose);
				myProg.WriteBinFile(outFile);
			}
			else
			{
				Console.WriteLine("Please pass a file to load");
			}
			//*/
			/* testing
			Program myProg = new Program();
			string inFile = "OBJ_FILES/Cube.obj";
			//string inFile = "OBJ_FILES/GhoulOBJ.obj";
			//string inFile = "OBJ_FILES/Plane_BW.obj";
			//string inFile = "OBJ_FILES/gun.big";
			string outFile = inFile.Substring(0, inFile.Length - 4) + ".bin";
			myProg.LoadFile(inFile,2);
			myProg.WriteBinFile(outFile);
			myProg.PrintBinFile(outFile);
			//*/

		}
	}
}
