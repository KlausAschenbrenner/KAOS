void main()
{
	char *video_memory = (char *)0xFFFF8000000B8000;
	int i = 0;
	int j = 0;

	for (i = 0; i < 4000; i++)
	{
		video_memory[i] = 'K';

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


	/* // Print out "Klaus"
    char *video_memory = (char *)0xFFFF8000000B8000;
	video_memory[0] = 'K';
	video_memory[2] = 'l';
	video_memory[4] = 'a';
	video_memory[6] = 'u';
	video_memory[8] = 's';

    return; */
}