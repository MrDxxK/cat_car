#define buzzer_pin 10 //定义蜂鸣器驱动引脚

int song[] = {
	196, 261, 330, 392, 523, 659, 784, 659,
	207, 261, 311, 415, 523, 622, 831, 622,
	233, 294, 349, 466, 587, 698, 932, 932, 932, 932, 1046,
};

float noteDurations[] = {
	8, 8, 8, 8, 8, 8, 2.667, 2.667,
	8, 8, 8, 8, 8, 8, 2.667, 2.667,
	8, 8, 8, 8, 8, 8, 2.667, 8, 8, 8, 1,
};

void song_play()
{
	for (int thisNote = 0; thisNote < sizeof(noteDurations)/sizeof(float); thisNote++)
	{
		int noteDuration = 1000 / noteDurations[thisNote];
		tone(buzzer_pin, song[thisNote], noteDuration);
		int pauseBetweenNotes = noteDuration + 50;
		delay(noteDuration);
		noTone(buzzer_pin);
	}
}
