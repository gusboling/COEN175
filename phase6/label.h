#ifndef LABEL_H
#define LABEL_H

struct Label{
	static unsigned counter;
	unsigned number;
	Label(){number = counter++;}
};

unsigned Label::counter=0;

#endif //LABEL_H
