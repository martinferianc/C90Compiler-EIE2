int main() {
	int n = 123;
	int x = 4;

	{
		n = 5;
	}

	{ int n = 1123;
		{ int n = 340;
			{
				int n = 507;
			}
			return n;
		}
	}
}
