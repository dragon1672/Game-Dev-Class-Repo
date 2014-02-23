using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpOBJConverter
{
	class Vertex
	{
		private static Random rand = new Random();
		int? _id = null;
		private int ProgramId {
			get {
				if (_id == null)
				{
					_id = rand.Next();
				}
				return (int)_id;
			}
		}

		public static Vertex ParseVert(string data)
		{
			string[] elements = data.Split('/');
			int offset = elements.Length - 3;
			int pos = int.Parse(elements[offset + 0]) - 1;
			int uvs = int.Parse(elements[offset + 1]) - 1;
			int nor = int.Parse(elements[offset + 2]) - 1;
			return new Vertex(pos, uvs, nor);
		}

		public Vec3 Position; // parsed Data
		public readonly int NPosition; // index

		public Vec2 Uv; // parsed data
		public readonly int NUv; // index

		public Vec3 Normal; // parsed data
		public readonly int NNormal; // index

		public Vertex(int pos, int uv, int norm)
		{
			NPosition = pos;
			NUv = uv;
			NNormal = norm;
		}

		public override bool Equals(object obj)
		{
			if(obj.GetType()!=this.GetType()) return false;
			Vertex that = (Vertex)obj;
			if (this.NPosition != that.NPosition) return false;
			if (this.NUv != that.NUv) return false;
			if (this.NNormal != that.NNormal) return false;
			return true;
		}
		public override int GetHashCode()
		{
			const int prime = 761;
			int result = 1;
			result *= prime * NPosition;
			result *= prime * NUv;
			result *= prime * NNormal;
			return result;
		}
		public override string ToString()
		{
			return "{ Position: " + Position + ", "
			       + "UV: " + Uv + ", "
			       + "Normal: " + Normal+" }";
		}
	}
}
