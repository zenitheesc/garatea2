#ifdef BUZZ_H
#define BUZZ_H

public class BUZZ
{
public:
	BUZZ(int buzzPin);
	~BUZZ();
	
	enum{
		ON,
		OFF
	};

	void beep(void); // Toque intermitente a cada segundo
	void beeper(int n); // 
	int getBuzzPin();
private:
	const int buzzPin = 0; // Information for some function who needs this
};


#endif