#include "TextBox.h"
#include <iostream>

TextBox::TextBox(int x, int y)
{
	setPos(x, y);
}

TextBox::TextBox(int x, int y, std::string text)
{
	print(text);
	setPos(x, y);
}

TextBox::TextBox(int x, int y, std::string text, float scale)
{
	print(text);
	setPos(x, y);
	setScale(scale);
}

TextBox::TextBox(int x, int y, std::string text, float scale, Color color)
{
	print(text);
	setPos(x, y);
	setColor(color);
	setScale(scale);
}

void TextBox::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void TextBox::setPos(Point p)
{
	this->x = p.x;
	this->y = p.y;
}

void TextBox::setColor(Color color)
{
	this->color = color;
}

void TextBox::drawChar(Canvas& canvas, char c)
{
	int tail_shift = 0;
	int width_reduce = 0;
	
	switch (c)
	{
	case 'g':
	case 'p':
	case 'q':
	case 'y':
		tail_shift = 3;
		break;
	case ',':
	case 'j':
		tail_shift = 1;
		break;
	case 'i':
	case 'l':
		width_reduce = 0;
		break;
	case '\n':
		cursor_x = 0;
		cursor_y += 12;
		return;
	default:
		break;
	}

	Color* buffer = new Color[55];
	for (int i = 0; i < 55; i++)
		buffer[i] = Color::ALPHA;


	for (int i = width_reduce; i < 4; i++) for (int j = 0; j < 8; j++)
		if ((letters[c].bytes[0] << j + i * 8) & 0x80000000)
		{
			buffer[i + 5 * (j + tail_shift)] = color;

			//canvas.lerpDrawPoint(Point(x + (cursor_x + i) * scale, y + (cursor_y + j + tail_shift) * scale), scale, color);

			//for (int k = 0; k < scale; k++) for (int l = 0; l < scale; l++)
			//	canvas.drawPoint(x + cursor_x + i * scale + k, y + cursor_y + (j + tail_shift) * scale + l, color);
		}
	if (!width_reduce)
		for (int j = 0; j < 8; j++)
			if ((letters[c].bytes[1] << j) & 0x80000000)
			{
				buffer[4 + 5 * (j + tail_shift)] = color;

				//canvas.lerpDrawPoint(Point(x + (cursor_x + 4) * scale, y + (cursor_y + j) * scale), scale, color);
				
				//for (int k = 0; k < scale; k++) for (int l = 0; l < scale; l++)
				//	canvas.drawPoint(x + cursor_x + 4 * scale + k, y + cursor_y + (j + tail_shift) * scale + l, color);
			}
	//canvas.drawMatrix(x + cursor_x * scale, y + cursor_y * scale, 5, 11, buffer);
	canvas.lerpDrawMatrix(Point(x + cursor_x * scale, y + cursor_y * scale), 5, 11, scale, buffer); 
	cursor_x += 6;
	delete[] buffer;
}

void TextBox::draw(Canvas &canvas)
{
//	std::cout << "drawing text: ";
	char* text = new char[this->text.length() + 1];
	strcpy_s(text, this->text.length() + 1, this->text.c_str());
	
	int length = this->text.length();
	for(int c = 0; c < length; c++)
	{
		drawChar(canvas, text[c]);
	}
	cursor_x = 0;
	cursor_y = 0;
}

int TextBox::getLength()
{
	return text.length();
}

float TextBox::getScale()
{
	return scale;
}

void TextBox::setScale(float scale)
{
	this->scale = scale;
}

void TextBox::print(std::string text)
{
	this->text += text;
}
void TextBox::print(double val)
{
	std::stringstream s;
	std::string temp;
	s << val;
	s >> temp;
	print(temp);
}

void TextBox::clear()
{
	text = std::string();
}

LetterBits TextBox::letters[128] = 
{
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{0x00000000, 0x00000000},		// ' '
	{0x0000fd00, 0x00000000},		// '!'
	{0x00e000e0, 0x00000000},		// '"'
	{0x24ff24ff, 0x24000000},		// '#'
	{0x724aff4a, 0x46000000},		// '$'
	{0xc1c61863, 0x83000000},		// '%'
	{0x6e919966, 0x09000000},		// '&'
	{0x0000e000, 0x00000000},		// '''
	{0x007e8100, 0x00000000},		// '('
	{0x0000817e, 0x00000000},		// ')'
	{0xa040e040, 0xa0000000},		// '*'
	{0x08083e08, 0x08000000},		// '+'
	{0x00010600, 0x00000000},		// ','
	{0x08080808, 0x08000000},		// '-'
	{0x00000100, 0x00000000},		// '.'
	{0x01061860, 0x80000000},		// '/'
	{0x7e8599a1, 0x7e000000},		// '0'
	{0x2141ff01, 0x01000000},		// '1'
	{0x83858991, 0x61000000},		// '2'
	{0x91919191, 0x6e000000},		// '3'
	{0x182848ff, 0x08000000},		// '4'
	{0xf1919191, 0x8e000000},		// '5'
	{0x7e919191, 0x4e000000},		// '6'
	{0x80818698, 0xe0000000},		// '7'
	{0x46a991a9, 0x46000000},		// '8'
	{0x72898989, 0x7e000000},		// '9'
	{0x00002400, 0x00000000},		// ':'
	{0x00012600, 0x00000000},		// ';'
	{0x08141422, 0x22000000},		// '<'
	{0x14141414, 0x14000000},		// '='
	{0x22221414, 0x08000000},		// '>'
	{0x60808988, 0x60000000},		// '?'
	{0x7e819981, 0x7d000000},		// '@'
	{0x7f888888, 0x7f000000},		// 'A'
	{0xff919191, 0x6e000000}, 	// 'B'
	{0x7e818181, 0x81000000}, 	// 'C'
	{0xff818181, 0x7e000000}, 	// 'D'
	{0xff919191, 0x91000000}, 	// 'E'
	{0xff909090, 0x90000000}, 	// 'F'
	{0x7e81898a, 0x8f000000}, 	// 'G'
	{0xff101010, 0xff000000}, 	// 'H'
	{0x0081ff81, 0x00000000}, 	// 'I
	{0x02010101, 0xfe000000}, 	// 'J'
	{0xff102844, 0x83000000}, 	// 'K'
	{0xff010101, 0x01000000}, 	// 'L'
	{0xff402040, 0xff000000}, 	// 'M'
	{0xff601806, 0xff000000}, 	// 'N'
	{0x7e818181, 0x7e000000}, 	// 'O'
	{0xff888888, 0x70000000}, 	// 'P'
	{0x7e818583, 0x7f000000}, 	// 'Q'
	{0xff888888, 0x77000000}, 	// 'R'
	{0x61919191, 0x8e000000}, 	// 'S'
	{0x8080ff80, 0x80000000}, 	// 'T'
	{0xfe010101, 0xfe000000}, 	// 'U'
	{0xf8060106, 0xf8000000}, 	// 'V'
	{0xff020402, 0xff000000}, 	// 'W'
	{0xe3140814, 0xe3000000}, 	// 'X'
	{0xe0100f10, 0xe0000000}, 	// 'Y'
	{0x838599a1, 0xc1000000}, 	// 'Z'
	{0x0000ff81, 0x00000000},		// '['
	{0x80601806, 0x01000000},		// '\'
	{0x0081ff00, 0x00000000},		// ']'	
	{0x20408040, 0x20000000},		// '^'
	{0x01010101, 0x01000000},		// '_'
	{(unsigned int)~0x0, (unsigned int)~0x0},
	{0x1215150e, 0x01000000},		// 'a'
	{0xff111111, 0x0e000000},		// 'b'
	{0x0e111111, 0x11000000},		// 'c'
	{0x0e111111, 0xff000000},		// 'd'
	{0x0e151515, 0x09000000},		// 'e'
	{0x10107f90, 0x90000000},		// 'f'
	{0x71898989, 0xfe000000},		// 'g'
	{0xff101010, 0x0f000000},		// 'h'
	{0x00005f00, 0x00000000},		// 'i'
	{0x00020101, 0xbe000000},		// 'j'
	{0xff040814, 0x23000000},		// 'k'
	{0x0000ff00, 0x00000000},		// 'l'
	{0x1f101f10, 0x0f000000},		// 'm'
	{0x1f101010, 0x0f000000},		// 'n'
	{0x0e111111, 0x0e000000},		// 'o'
	{0xff888888, 0x70000000},		// 'p'
	{0x70888888, 0xff000000},		// 'q'
	{0x1f081010, 0x10000000},		// 'r'
	{0x09151515, 0x12000000},		// 's'
	{0x1010fe11, 0x11000000},		// 't'
	{0x1e010101, 0x1f000000},		// 'u'
	{0x1c020102, 0x1c000000},		// 'v'
	{0x1e010601, 0x1e000000},		// 'w'
	{0x110a040a, 0x11000000},		// 'x'
	{0xc1320c30, 0xc0000000},		// 'y'
	{0x11131519, 0x11000000},		// 'z'
	{0x08768181, 0x00000000},		// '{'
	{0x0000ff00, 0x00000000},		// '|'
	{0x00818176, 0x08000000},		// '}'
	{0x08101008, 0x10000000},		// '~'
	{(unsigned int)~0x0, (unsigned int)~0x0}
};
