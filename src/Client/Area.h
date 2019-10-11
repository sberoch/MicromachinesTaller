#ifndef __AREA_H_
#define __AREA_H_

class Area {
public:
	Area();
	void set(int x, int y, int width, int height);
	Area(int x, int y, int width, int height);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	bool estaAdentro(int x, int y);
private:
	int x, y;
	int width, height;
};

#endif
