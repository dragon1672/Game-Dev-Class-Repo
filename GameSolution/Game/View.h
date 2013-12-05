#pragma once
#ifndef VIEW_H
#define VIEW_H

class MyGraphics;

class View {
public:
	virtual bool update(float dt)=0;//true mean it is complete
	virtual void draw(MyGraphics& graphics)=0;
};

#endif