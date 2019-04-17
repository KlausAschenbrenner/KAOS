void main()
{
	char *video_memory = (char *)0xFFFF8000000B8000;
	int i = 0;
	int j = 0;

	for (i = 3999; i >= 0; i--)
	{
		video_memory[i] = 'A';

		for (j = 0; j < 100000; j++)
		{
			int a;
			int b;
			int c;
			a = 1;
			b = 1;
			c = a + b;
		}
	}

	while (1 == 1);
}