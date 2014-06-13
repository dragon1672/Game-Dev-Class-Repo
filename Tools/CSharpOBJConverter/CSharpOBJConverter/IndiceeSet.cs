using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpOBJConverter
{
	class IndiceeSet :IParser
	{
		//these 3 make a single triangle
		public Vertex One;
		public Vertex Two;
		public Vertex Thr;
		public List<Vertex> verts = new List<Vertex>();


		public void Parse(string data)
		{
			string[] split = data.Split();
			for (int i = 1; i < split.Count(); i++)
			{
				verts.Add(Vertex.ParseVert(split[i]));
			}
			One = Vertex.ParseVert(split[1]);
			Two = Vertex.ParseVert(split[2]);
			Thr = Vertex.ParseVert(split[3]);
		}
	}
}
