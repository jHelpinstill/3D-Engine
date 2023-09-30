#include "Textbox.h"
#include <iostream>
Textbox::Textbox(int x, int y, int width, int height)
{
	setPos(x, y);
	setSize(width, height);
}
Textbox::Textbox(int x, int y, int width, int height, std::string text, float scale, Color color, Adjustment adjustment, std::string name)
{
	setPos(x, y);
	setSize(width, height);
	setTextColor(color);
	setTextScale(scale);
	setName(name);
	this->adjustment = adjustment;
	print(text);
	render();
}

void Textbox::setTextScale(float scale)
{
	this->text_scale = scale;
}

void Textbox::setTextColor(Color color)
{
	this->text_color = color;
}

void Textbox::setAdjustment(Adjustment  adjustment)
{
	this->adjustment = adjustment;
}

void Textbox::drawChar(Canvas& canvas, char c)
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
	case ' ':
		cursor_x += 6;
		break;
	default:
		break;
	}

	Color* buffer = new Color[55];
	for (int i = 0; i < 55; i++)
		buffer[i] = Color::ALPHA;


	for (int i = width_reduce; i < 4; i++) for (int j = 0; j < 8; j++)
		if ((letters[c].bytes[0] << j + i * 8) & 0x80000000)
		{
			buffer[i + 5 * (j + tail_shift)] = text_color;
		}
	if (!width_reduce)
		for (int j = 0; j < 8; j++)
			if ((letters[c].bytes[1] << j) & 0x80000000)
			{
				buffer[4 + 5 * (j + tail_shift)] = text_color;
			}
	//canvas.lerpDrawMatrix(Point(cursor_x * text_scale, cursor_y * text_scale), 5, 11, text_scale, buffer); 
	canvas.drawMatrix(cursor_x * text_scale, cursor_y * text_scale, 5, 11, buffer, true); 
	cursor_x += 6;
	delete[] buffer;
}

void Textbox::render()
{
	Canvas canvas(body);

	int width_in_chars = body.getWidth() / (6 * text_scale);
	cursor_y = 0;

	switch (adjustment)
	{
	case Adjustment::LEFT:
	{
		int char_cursor = 0;
		std::string next_word;
		for (int c = 0; c < text.length(); c++)
		{
			if (char_cursor >= width_in_chars)
			{
				cursor_x = 0;
				cursor_y += 12 * text_scale;
				char_cursor = 0;
			}
			char next_char = text.at(c);
			switch (next_char)
			{
			case ' ':
			{
				for (int i = 0; i < next_word.length(); i++)
					drawChar(canvas, next_word.at(i));
				next_word.clear();
				char_cursor++;
				continue;
			}
			case '\n':
			{
				for (int i = 0; i < next_word.length(); i++)
					drawChar(canvas, next_word.at(i));
				next_word.clear();
				char_cursor = 0;
				cursor_x = 0;
				cursor_y += 12 * text_scale;
				continue;
			}
			default:
			{
				next_word += next_char;
				char_cursor++;
			}
			}

			if (next_word.length() == width_in_chars)
			{
				for (int i = 0; i < next_word.length(); i++)
					drawChar(canvas, next_word.at(i));
				next_word.clear();
				char_cursor = 0;
				continue;
			}
			else if (char_cursor == width_in_chars)
			{
				cursor_x = 0;
				cursor_y += 12 * text_scale;
				char_cursor = next_word.length();
			}

		}
		//cursor_x = 0;
		//int char_cursor = 0;
		//int c = 0;
		//while (c < text.length())
		//{
		//	int next_word_length = 0;
		//	char next_char;
		//	do
		//	{
		//		next_char = text.at(c + next_word_length++);
		//	} while (next_char != ' ' && next_char != '\n' && c + next_word_length < text.length());
		//	next_word_length--;
		//
		//	if (next_word_length > width_in_chars)
		//	{
		//		next_word_length = width_in_chars - char_cursor;
		//		if (next_word_length <= 0)
		//		{
		//			next_word_length = width_in_chars;
		//			cursor_y += 12;
		//			cursor_x = 0;
		//			char_cursor = 0;
		//		}
		//	}
		//	else if (char_cursor + next_word_length > width_in_chars)
		//	{
		//		cursor_y += 12;
		//		cursor_x = 0;
		//		char_cursor = 0;
		//	}
		//	for (int i = 0; i < next_word_length; i++)
		//	{
		//		drawChar(canvas, text.at(c++));
		//		char_cursor++;
		//	}
		//	if (next_char == '\n')
		//	{
		//		cursor_y += 12;
		//		cursor_x = 0;
		//		char_cursor = 0;
		//	}
		//	else
		//	{
		//		drawChar(canvas, ' ');
		//		char_cursor++;
		//	}
		//}
		break;
	}
	case Adjustment::CENTER:
	{
		int chars_in_line = 0;
		int c = 0;
		while (c < text.length())
		{
			int line_length = 0;
			char next_char;
			while (1)
			{
				int next_word_length = 0;

				do
				{
					next_char = text.at(c + line_length + next_word_length++);
				} while (next_char != ' ' && next_char != '\n' && c + next_word_length < text.length());
				next_word_length--;

				if (chars_in_line + next_word_length > width_in_chars)
					break;
				else
					line_length += next_word_length + 1;

				if (next_char == '\n')
					break;
			}
			cursor_x = ((width_in_chars - chars_in_line) * 6 * text_scale) / 2;

			for (int i = 0; i < line_length; i++)
				drawChar(canvas, text.at(c++));

			cursor_y += 12;
			chars_in_line = 0;
		}
		break;
	}
	case Adjustment::RIGHT:
	{
		break;
	}
	}
}

int Textbox::getLength()
{
	return text.length();
}

float Textbox::getScale()
{
	return text_scale;
}

void Textbox::print(std::string text)
{
	this->text += text;
}
void Textbox::print(double val)
{
	std::stringstream s;
	s << val;
	print(s.str());
}
void Textbox::print(int val, bool hex)
{
	std::stringstream s;
	s << val;
	if (hex)
		s >> std::hex;
	print(s.str());
}

void Textbox::clear()
{
	text = std::string();
}

LetterBits Textbox::letters[128] = 
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
