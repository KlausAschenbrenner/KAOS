void main()
{
	// Print out "Klaus"
    char *video_memory = (char *)0xFFFF8000000B8000;
	video_memory[0] = 'K';
	video_memory[2] = 'l';
	video_memory[4] = 'a';
	video_memory[6] = 'u';
	video_memory[8] = 's';

    return;
}