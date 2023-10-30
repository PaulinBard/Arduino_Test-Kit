#define l1 11
#define l2 8
#define l3 6
#define l4 9

#define l5 7
#define l6 10
#define l7 12
#define l8 13

#define c1 17 // ana3
#define c2 16 // ana2
#define c3 19 // ana5
#define c4 2

#define c5 4
#define c6 18 // ana4
#define c7 3
#define c8 5

// 2-dimensional array of row pin numbers:
const int row[8] = {
    l1, l2, l3, l4, l5, l6, l7, l8};

// 2-dimensional array of column pin numbers:
const int col[8] = {
    c1, c2, c3, c4, c5, c6, c7, c8};

// 2-dimensional array of pixels:
int pixel[8][8];

// cursor position:
int x = 5;
int y = 5;

int mat[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1}};
int mat1[8][8] = {
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const uint64_t smileysad = 0x00423c0000666600;
int sadsmiley[8][8];
 const uint64_t chop=  0x00f8fefaca8e8800;
void setup()
{
    Serial.begin(9600);
    // initialize the I/O pins as outputs iterate over the pins:
    for (int thisPin = 0; thisPin < 8; thisPin++)
    {
        // initialize the output pins:
        pinMode(col[thisPin], OUTPUT);
        pinMode(row[thisPin], OUTPUT);
        // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
        digitalWrite(col[thisPin], HIGH);
    }
    
    
    hexToMatrix(chop, sadsmiley);
    invertMatrix(sadsmiley);
}

void loop()
{
    // read input:
    // readSensors();
    // draw the screen:
    // refreshScreen();
    Serial.println("mat");
    // dessin(mat);
    refreshScreen(sadsmiley);
    // delay(1000);

    // Serial.println("reset");
    // reset();
    // delay(1000);
}
void dessin(int matrice[8][8])//marche pas
{
    for (int thisRow = 0; thisRow < 8; thisRow++)
    {
        for (int thisCol = 0; thisCol < 8; thisCol++)
        {
            if (matrice[thisRow][thisCol] == 1)
            {
                digitalWrite(row[thisRow], HIGH);
                digitalWrite(col[thisCol], LOW);
            }
        }
    }
}
void reset()
{
    for (int thisRow = 0; thisRow < 8; thisRow++)
    {
        for (int thisCol = 0; thisCol < 8; thisCol++)
        {

            digitalWrite(row[thisRow], LOW);
            digitalWrite(col[thisCol], HIGH);
        }
    }
}

void readSensors(int pixels[8][8])
{
    // turn off the last position:
    pixels[x][y] = HIGH;
    // read the sensors for X and Y values:
    x = 7 - map(analogRead(A0), 0, 1023, 0, 7);
    y = map(analogRead(A1), 0, 1023, 0, 7);
    // set the new pixel position low so that the LED will turn on in the next
    // screen refresh:
    pixels[x][y] = LOW;
}

void refreshScreen(int pixels[8][8])
{
    // iterate over the rows (anodes):
    for (int thisRow = 0; thisRow < 8; thisRow++)
    {
        // take the row pin (anode) high:
        digitalWrite(row[thisRow], HIGH);
        // iterate over the cols (cathodes):
        for (int thisCol = 0; thisCol < 8; thisCol++)
        {
            // get the state of the current pixel;
            int thisPixel = pixels[thisRow][thisCol];
            // when the row is HIGH and the col is LOW,
            // the LED where they meet turns on:
            digitalWrite(col[thisCol], thisPixel);

            // turn the pixel off:
            if (thisPixel == LOW)
            {
                digitalWrite(col[thisCol], HIGH);
            }
        }
        // take the row pin low to turn off the whole row:
        digitalWrite(row[thisRow], LOW);
    }
}

void hexToMatrix(uint64_t hexValue, int matrix[8][8])
{
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 7; j >= 0; --j)
        {
            matrix[i][j] = (hexValue & 1) ? 1 : 0;
            hexValue >>= 1;
        }
    }
}

void invertMatrix(int matrice[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            matrice[i][j] = (matrice[i][j] == 0) ? 1 : 0;
        }
    }
}