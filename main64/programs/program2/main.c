void main()
{
	// Print out "Karin"
    char *video_memory = (char *)0xFFFF8000000B8000;
	video_memory[0] = 'K';
	video_memory[2] = 'a';
	video_memory[4] = 'r';
	video_memory[6] = 'i';
	video_memory[8] = 'n';
	
    return;
}