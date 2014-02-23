using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpOBJConverter
{
	class Vec3 : IParser
	{
		public float X;
		public float Y;
		public float Z;

		public Vec3() { }
		public Vec3(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		public void Parse(string data)
		{
			string[] split = data.Split();
			int offset = split.Length - 3;
			X = float.Parse(split[offset+0]);
			Y = float.Parse(split[offset+1]);
			Z = float.Parse(split[offset+2]);
		}
		public override string ToString()
		{
			return "{ " + X + ", " + Y + ", " + Z + " }";
		}
	}
}
