using System;
using System.Collections;
using System.Text.RegularExpressions;

namespace ConsoleApp1
{
	class Rational : IComparable
	{
		private int n_;
		private int m_;

		public Rational(int n, int m)
		{
			n_ = n;
			m_ = (m > 0) ? m : 1;
		}

		public Rational(string rational)
		{
		
			Regex rgx = new Regex(@"/");
			string[] result = rgx.Split(rational);
			bool successHigher = int.TryParse(result[0], out int higher);
			if (successHigher == false)
			{
				n_ = 5;
			}
			else
			{
				n_ = higher;
			}
			bool successLower = int.TryParse(result[1], out int lower);
			if (successLower == false)
			{
				m_ = 5;
			}
			else
			{
				m_ = lower;
			}
		}

		public int N
		{
			get { return n_; }
			set { n_ = value; }
		}

		public int M
		{
			get { return m_; }
			set
			{
				if (value > 0)
					m_ = value;
				else
					throw new Exception("Число должно быть натуральным");
			}
		}

		public static Rational operator +(Rational a, Rational b)
		{
			Rational result = new Rational(1, 1);
			result.m_ = a.m_ * b.m_;
			result.n_ = a.n_ * b.m_ + b.m_ * a.n_;
			return result;
		}

		public static Rational operator -(Rational a, Rational b)
		{
			Rational result = new Rational(1, 1);
			result.m_ = a.m_ * b.m_;
			result.n_ = a.n_ * b.m_ - b.m_ * a.n_;
			return result;
		}

		public static bool operator <(Rational a, Rational b)
		{
			return a.n_ / a.m_ < b.n_ / b.m_;
		}

		public static bool operator >(Rational a, Rational b)
		{
			return a.n_ / a.m_ > b.n_ / b.m_;
		}

		public static implicit operator int(Rational r) => r.n_ / r.m_;
		public static explicit operator double(Rational r) => r.n_ / r.m_;

		public int CompareTo(object obj)
		{
			if (obj == null) { Console.WriteLine("wtf"); return 1; }
			Rational rational = obj as Rational;
			if (rational != null)
				return (this.n_ / this.m_).CompareTo(rational.n_ / rational.m_);
			else
				throw new ArgumentException("Objest is not a RationalNumber");
		}

		public override string ToString()
		{
			return string.Format("{0}/{1}", n_, m_);
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Enter rational number: ");
			string rat = Console.ReadLine();
			Rational strTest = new Rational(rat);
			Console.WriteLine(strTest.ToString());
			Rational first = new Rational(14, 5);
			int num = first;
			double n = first;
			Console.WriteLine("int " + num + " double " + n);
			Console.WriteLine(first.ToString());
			Rational second = new Rational(3, 2);
			Rational result = first + second;
			Console.WriteLine(first < second);
			Console.WriteLine(first > second);
			Console.WriteLine("Compare " + second.CompareTo(first));
			Console.ReadLine();
		}
	}
}