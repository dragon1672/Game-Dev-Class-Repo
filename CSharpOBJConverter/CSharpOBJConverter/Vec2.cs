using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpOBJConverter
{
	class Vec2 : IParser
	{
		public float X;
		public float Y;

		public Vec2() { }
		public Vec2(float x, float y)
		{
			X = x;
			Y = y;
		}

		public void Parse(string data)
		{
			string[] split = data.Split();
			X = float.Parse(split[1]);
			Y = float.Parse(split[2]);
		}
		public override string ToString()
		{
			return "{ " + X + ", " + Y + " }";
		}
	}
}
