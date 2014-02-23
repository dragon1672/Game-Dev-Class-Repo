using System;
using System.Collections.Generic;

namespace CSharpOBJConverter
{
	internal class LineParse<T> : ILineParser where T : IParser, new()
	{
		public List<T> ParsedData = new List<T>();
		public readonly string LineStr; // the string that determins the line

		private Action<T> AddDataCallback;

		public LineParse(string toMatch, Action<T> addCallback=null)
		{
			LineStr = toMatch;
			AddDataCallback = addCallback;
		}
		public bool IsLine(string data)
		{
			return (data.Split()[0] == LineStr);
		}
		public void AddData(string line)
		{
			var T = new T();
			T.Parse(line);
			ParsedData.Add(T);
			if(AddDataCallback!=null) AddDataCallback(T);
		}
	}
}
