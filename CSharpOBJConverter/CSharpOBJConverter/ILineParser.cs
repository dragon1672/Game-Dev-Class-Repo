using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpOBJConverter
{
	interface ILineParser
	{
		bool IsLine(string data);
		void AddData(string line);
	}
}
