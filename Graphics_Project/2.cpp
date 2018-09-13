#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<string.h>
#include<unistd.h>
#include<windows.h>
#include<mmsystem.h>
#include <fstream>
using namespace std;
//Declare Necessary variable
void update(int);
void check();
void makedelay(int);
void FindClash();
void writeIntoFile();
void villainUpdate(int value);
float _position=0;
double speed = 0.0;

float savedSpeed = 0.0f;
bool paused = false;
bool over = false;
bool start = true;

bool isRight = true;
float mouseX,mouseY ;

void keyboard(unsigned char key, int x, int y);
double _VillainSpeed = 0.0;
double _VillainSavedSpeed = 0.0;

float _targetPosX=-0.085;
float _targetPosY=-0.42;

float _bodyguardPosX=-0.03;
float _bodyguardPosY=-0.1;

float _villain1PosX=-0.8;
float _villain1PosY=.8;
float _villain1X=0;
float _villain1Y=0;

float _villain2PosX=-0.3;
float _villain2PosY=.8;
float _villain2X=0;
float _villain2Y=0;

float _villain3PosX=0.3;
float _villain3PosY=.8;
float _villain3X=0;
float _villain3Y=0;

float _villain4PosX=0.8;
float _villain4PosY=.8;
float _villain4X=0;
float _villain4Y=0;

int score=0;
int hscore=0;
int level=0;

char text[40];
char text1[40];
char finalText[500];

char scoreText[] = "00";
char scoreText1[] = "00";

char Score[100],ch;

float getw(int w)
{
    return (float)w/glutGet(GLUT_WINDOW_WIDTH)/2;
}

float geth(int h)
{
    return (float)h/glutGet(GLUT_WINDOW_HEIGHT)/2;
}
///Text Writing
void Sprint( float x, float y, char *st)
{
    int l,i;


    l=strlen( st ); // see how many characters are in text string.
    glColor3f(0.0,1.0,0.7);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }
}
void displayRasterText(float x,float y,float z,char *stringToDisplay)
{
    int length;
    glRasterPos3f(x, y, z);
    length = strlen(stringToDisplay);

    for(int i=0 ; i<length ; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,stringToDisplay[i]);
    }
}

///Keyboard Input
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if(_bodyguardPosX < -.11) {}
        else
        {
            _bodyguardPosX-=0.01;
        }
        //sndPlaySound(TEXT("F://beep-02.wav"),SND_ASYNC);
        break;
    case GLUT_KEY_RIGHT:
        if(_bodyguardPosX > 0.08) {}
        else
        {
            _bodyguardPosX+=.01;
        }
        //sndPlaySound(TEXT("F://beep-02.wav"),SND_ASYNC);
        break;

    }
}
void drawScene()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective

    glMatrixMode(GL_MODELVIEW);
    if(start)
    {

        sprintf(text1,"Press S to start game...");
        glColor3ub(128,0,0);
        displayRasterText(-0.45,-0.0,0.0,text1);

        sprintf(text1,"Press ESC to quit game...");
        displayRasterText(-0.45,-0.2,0.0,text1);

    }
    else
    {

        if(over)
        {
            glColor3ub(147,0,0);
            sprintf(text1,"Game Over");
            displayRasterText(-0.15,0.1,0.0,text1);
            sprintf(text1,"Your Score : %d",score);
            displayRasterText(-0.20,0.0,0.0,text1);
            sprintf(text1,"High Score : %d",hscore);
            displayRasterText(-0.2,-0.1,0.0,text1);
            sprintf(text1,"Press ENTER to restart game again...");
            displayRasterText(-0.45,-0.2,0.0,text1);
            sprintf(text1,"Press ESC to quit game...");
            displayRasterText(-0.45,-0.3,0.0,text1);
            if(hscore < score)
            {
                hscore = score;
                writeIntoFile();
            }
        }
        else
        {

/// Screen Draw Initial Part
                glPushMatrix();
                glScalef(4,2,0);
                glPointSize(5);
             ///upper part design:
            glBegin(GL_QUADS);
            if(score>=40 && score<60)
            {
                 glColor3ub(93, 112, 170);
            }

            else if(score>=60 && score<80)
            {
                glColor3ub(62, 74, 113);
            }

            else if(score>=80 && score<100)
            {
                glColor3ub(41, 49, 75);
            }

            else if(score>=100 && score<120)
            {
                glColor3ub(27, 32, 50);
            }

            else if(score>=120 && score<140)
            {
                glColor3ub(18, 21, 33);
            }

            else if(score>=140 && score<160)
            {
                glColor3ub(12, 14, 22);
            }
              else
              {
                  glColor3ub(140,169,255);
              }
                //glColor3f(0.69,1.0,1.0);
                    //glScalef(2,2,0);
                    glVertex2f(getw(-700),geth(700));
                    glVertex2f(getw(700),geth(700));
                    glVertex2f(getw(700),geth(-500));
                    glVertex2f(getw(-700),geth(-500));
                    glEnd();


                ///LowerPart of screen
                ///Design of Object Place
                glBegin(GL_QUADS);
                //glColor3f(0,1.0,0.0);
                glColor3ub(69,209,14);
                //glScalef(2,2,0);
                glVertex2f(getw(-700),geth(-500));
                glVertex2f(getw(-700),geth(-700));
                glVertex2f(getw(700),geth(-700));
                glVertex2f(getw(700),geth(-500));
                glEnd();

                ///Tree Design
                /*glBegin(GL_QUADS);
                glColor3f(0,0,0);
                glVertex2f(getw(250), geth(-520));
                glVertex2f(getw(250), geth(-550));
                glVertex2f(getw(290), geth(-550));
                glVertex2f(getw(290), geth(-520));
                glEnd();
                glBegin(GL_TRIANGLES);
                glColor3f(0,1,0);
                glVertex2f(getw(200), geth(-480));
                glVertex2f(getw(280), geth(-420));
                glVertex2f(getw(350), geth(-480));
                glEnd();
                glBegin(GL_TRIANGLES);
                glColor3f(0,1,0);
                glVertex2f(getw(230), geth(-520));
                glVertex2f(getw(270), geth(-480));
                glVertex2f(getw(310), geth(-520));
                glEnd();
                glBegin(GL_TRIANGLES);
                glColor3f(0,1,0);
                glVertex2f(getw(210), geth(-500));
                glVertex2f(getw(270), geth(-440));
                glVertex2f(getw(330), geth(-500));
                glEnd();*/

                /// Main Target
                glTranslatef(_targetPosX,_targetPosY,0.0);
                glBegin(GL_QUADS);
                if(score>=40)
                {
                    glColor3ub(184,61,186);
                }
                else{
                    glColor3ub(196,255,14);
                }

                glScalef(2,2,0);
                glVertex2f(0,0);
                glVertex2f(0,.15);
                glVertex2f(.2,.15);
                glVertex2f(.2,0);
                glEnd();
                glPopMatrix();


                glPushMatrix();
                glScalef(4,2,0);
                glPointSize(5);

   ///Move Object Place Design

               if(score>=55){
                glBegin(GL_QUADS);
                glColor3ub(195,195,195);
                glVertex2f(getw(-700),geth(0));
                glVertex2f(getw(-700),geth(-360));
                glVertex2f(getw(700),geth(-360));
                glVertex2f(getw(700),geth(0));
                glEnd();}
                else{}

    /// Bodyguard
                glTranslatef(_bodyguardPosX,0.0,0.0);

                glBegin(GL_QUADS);

                glScalef(2,2,0);

                glBegin(GL_QUADS);
                 glColor3ub(136,0,27);
                glScalef(2,2,0);
                glVertex2f(_bodyguardPosX,_bodyguardPosY);
                glVertex2f(_bodyguardPosX,_bodyguardPosY-.1);
                glVertex2f(_bodyguardPosX+.08,_bodyguardPosY-.1);
                glVertex2f(_bodyguardPosX+.08,_bodyguardPosY);
                glEnd();

                glPopMatrix();
                glColor3f(0.66,0.27,0.18);
                sprintf(text,"SCORE = %d",score);
                displayRasterText(0.5,0.9,0.0,text);


                sprintf(text1,"Level = %d",level);
                displayRasterText(0.1,0.9,0.0,text1);
    /// Villain 1
                glPushMatrix();
                glTranslatef(_villain1PosX,_villain1PosY,0.0);

                glBegin(GL_QUADS);
                glColor3ub(108,64,49);
                glScalef(2,2,0);
                glVertex2f(_villain1X,_villain1Y);
                glVertex2f(_villain1X,_villain1Y-.140);
                glVertex2f(_villain1X+.15,_villain1Y-.140);
                glVertex2f(_villain1X+.15,_villain1Y);
                glEnd();

                glBegin(GL_QUADS);
                glColor3ub(0,0,49);
                glScalef(2,2,0);
                glVertex2f(_villain1X+.05,_villain1Y-.05);
                glVertex2f(_villain1X+.05,_villain1Y-.135);
                glVertex2f(_villain1X+.1,_villain1Y-.135);
                glVertex2f(_villain1X+.1,_villain1Y-.05);

                glEnd();
                glColor3ub(0,0,255);
                glTranslatef(_villain1X+0.075,_villain1Y-0.03,0.0);
                glutSolidSphere(0.02,25,20);

                glPopMatrix();

    /// Villain 2
                glPushMatrix();
                glTranslatef(_villain2PosX,_villain2PosY,0.0);

                glBegin(GL_QUADS);
                glColor3ub(225,13,134);
                glScalef(2,2,0);
                glVertex2f(_villain2X,_villain2Y);
                glVertex2f(_villain2X,_villain2Y-.140);
                glVertex2f(_villain2X+.15,_villain2Y-.140);
                glVertex2f(_villain2X+.15,_villain2Y);
                glEnd();

                 glBegin(GL_QUADS);
                glColor3ub(0,0,49);
                glScalef(2,2,0);
                glVertex2f(_villain2X+.05,_villain2Y-.05);
                glVertex2f(_villain2X+.05,_villain2Y-.135);
                glVertex2f(_villain2X+.1,_villain2Y-.135);
                glVertex2f(_villain2X+.1,_villain2Y-.05);
                glEnd();
                 glColor3ub(0,0,255);
                glTranslatef(_villain2X+0.075,_villain2Y-0.03,0.0);
                glutSolidSphere(0.02,25,20);

                FindClash();
                glPopMatrix();

    /// Villain 3
                glPushMatrix();
                glTranslatef(_villain3PosX,_villain3PosY,0.0);

                glBegin(GL_QUADS);
                glColor3ub(255,0,0);
                glScalef(2,2,0);

                glVertex2f(_villain3X,_villain3Y);
                glVertex2f(_villain3X,_villain3Y-.140);
                glVertex2f(_villain3X+.15,_villain3Y-.140);
                glVertex2f(_villain3X+.15,_villain3Y);
                glEnd();

                 glBegin(GL_QUADS);
                glColor3ub(0,0,49);
                glScalef(2,2,0);
                glVertex2f(_villain3X+.05,_villain3Y-.05);
                glVertex2f(_villain3X+.05,_villain3Y-.135);
                glVertex2f(_villain3X+.1,_villain3Y-.135);
                glVertex2f(_villain3X+.1,_villain3Y-.05);

                glEnd();
                 glColor3ub(0,0,255);
                glTranslatef(_villain3X+0.075,_villain3Y-0.03,0.0);
                glutSolidSphere(0.02,25,20);
                FindClash();
                glPopMatrix();

    /// Villain 4
                glPushMatrix();
                glTranslatef(_villain4PosX,_villain4PosY,0.0);

                glBegin(GL_QUADS);
                glColor3ub(255,0,150);
                glScalef(2,2,0);
                glVertex2f(_villain4X,_villain4Y);
                glVertex2f(_villain4X,_villain4Y-.140);
                glVertex2f(_villain4X+.15,_villain4Y-.140);
                glVertex2f(_villain4X+.15,_villain4Y);

                //glTranslatef(_villain4X+0.5,_villain4PosY);
                //glutSolidSphere(0.01,50,50);
                glEnd();
                 glBegin(GL_QUADS);
                glColor3ub(0,0,49);
                glScalef(2,2,0);
                glVertex2f(_villain4X+.05,_villain4Y-.05);
                glVertex2f(_villain4X+.05,_villain4Y-.135);
                glVertex2f(_villain4X+.1,_villain4Y-.135);
                glVertex2f(_villain4X+.1,_villain4Y-.05);

                glEnd();
                 glColor3ub(0,0,255);
                glTranslatef(_villain4X+0.075,_villain4Y-0.03,0.0);
                glutSolidSphere(0.02,25,20);
                FindClash();

                glPopMatrix();

                glPushMatrix();
        glColor3f(1.0f,0.0f,0.0f);
        if(score>=40 & score<60)
        {
            glScalef(2,2,0);
            glBegin(GL_POLYGON);
            glVertex2f(getw(-600),geth(600));
            glVertex2f(getw(-580),geth(580));
            glVertex2f(getw(-560),geth(580));
            glVertex2f(getw(-580),geth(560));
            glVertex2f(getw(-580),geth(540));PlaySound(TEXT("1.wav"),NULL,SND_ASYNC);
            glVertex2f(getw(-600),geth(560));
            glVertex2f(getw(-620),geth(540));
            glVertex2f(getw(-620),geth(560));
            glVertex2f(getw(-640),geth(580));
            glVertex2f(getw(-620),geth(580));
           glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(getw(-660),geth(660));
            glVertex2f(getw(-640),geth(640));
            glVertex2f(getw(-620),geth(640));
            glVertex2f(getw(-640),geth(620));
            glVertex2f(getw(-640),geth(600));
            glVertex2f(getw(-660),geth(620));
            glVertex2f(getw(-680),geth(600));
            glVertex2f(getw(-680),geth(620));
            glVertex2f(getw(-700),geth(640));
            glVertex2f(getw(-680),geth(640));
           glEnd();
           glBegin(GL_POLYGON);
            glVertex2f(getw(-460),geth(540));
            glVertex2f(getw(-440),geth(520));
            glVertex2f(getw(-420),geth(520));
            glVertex2f(getw(-440),geth(500));
            glVertex2f(getw(-440),geth(480));
            glVertex2f(getw(-460),geth(500));
            glVertex2f(getw(-480),geth(480));
            glVertex2f(getw(-480),geth(500));
            glVertex2f(getw(-500),geth(520));
            glVertex2f(getw(-480),geth(520));
           glEnd();


           glBegin(GL_POLYGON);
            glVertex2f(getw(600),geth(600));
            glVertex2f(getw(580),geth(580));
            glVertex2f(getw(560),geth(580));
            glVertex2f(getw(580),geth(560));
            glVertex2f(getw(580),geth(540));
            glVertex2f(getw(600),geth(560));
            glVertex2f(getw(620),geth(540));
            glVertex2f(getw(620),geth(560));
            glVertex2f(getw(640),geth(580));
            glVertex2f(getw(620),geth(580));
           glEnd();

             glBegin(GL_POLYGON);
            glVertex2f(getw(540),geth(540));
            glVertex2f(getw(520),geth(520));
            glVertex2f(getw(500),geth(520));
            glVertex2f(getw(520),geth(500));
            glVertex2f(getw(520),geth(480));
            glVertex2f(getw(540),geth(500));
            glVertex2f(getw(560),geth(480));
            glVertex2f(getw(560),geth(500));
            glVertex2f(getw(580),geth(520));
            glVertex2f(getw(560),geth(520));
           glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(getw(460),geth(540));
            glVertex2f(getw(440),geth(520));
            glVertex2f(getw(420),geth(520));
            glVertex2f(getw(440),geth(500));
            glVertex2f(getw(440),geth(480));
            glVertex2f(getw(460),geth(500));
            glVertex2f(getw(480),geth(480));
            glVertex2f(getw(480),geth(500));
            glVertex2f(getw(500),geth(520));
            glVertex2f(getw(480),geth(520));
           glEnd();

        }
        else
         {glTranslatef(-.90,.90,0);
        glutSolidSphere(0.1,50,50);
    glPopMatrix();}
            }
        }

    glutSwapBuffers();
}

void check()
{

}
void update(int value)
{
    if(!paused)
    {
        _position = speed;
        if(isRight)
        {
            if(_targetPosX >= .05)
            {
                isRight = false;
            }
            else
            {
                _targetPosX+= .001;
            }

        }
        else
        {
            if(_targetPosX <= -.25)
            {
                isRight = true;
            }
            else
            {
                _targetPosX-= .001;
            }
        }

        _VillainSpeed-=.00005;      /// Villain Speed

        _villain1Y+=_VillainSpeed;
        _villain2Y+=_VillainSpeed;
        _villain3Y+=_VillainSpeed;
        _villain4Y+=_VillainSpeed;
        _position = speed;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);

}
///Villain Speed update
void villainUpdate(int value)
{

}
///Villain Movement
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        exit(0);
        break;

    case 83:    /// S for start the game

        start = false;
            over = false;
            _position=0;
            speed = 0.0;
            savedSpeed = 0.0f;
            paused = false;
            over = false;

            isRight = true;
            _VillainSpeed = 0.0;
            _VillainSavedSpeed = 0.0;

            _targetPosX=-0.085;
            _targetPosY=-0.42;

            _bodyguardPosX=-0.03;
            _bodyguardPosY=-0.1;

            _villain1PosX=-0.8;
            _villain1PosY=.8;
            _villain1X=0;
            _villain1Y=0;

            _villain2PosX=-0.3;
            _villain2PosY=.8;
            _villain2X=0;
            _villain2Y=0;

            _villain3PosX=0.3;
            _villain3PosY=.8;
            _villain3X=0;
            _villain3Y=0;

            _villain4PosX=0.8;
            _villain4PosY=.8;
            _villain4X=0;
            _villain4Y=0;

            score=0;
            level=0;

        break;

    case 13:  ///Enter
        if(over)
        {
            over = false;
            _position=0;
            speed = 0.0;
            savedSpeed = 0.0f;
            paused = false;
            over = false;

            isRight = true;
            _VillainSpeed = 0.0;
            _VillainSavedSpeed = 0.0;

            _targetPosX=-0.085;
            _targetPosY=-0.42;

            _bodyguardPosX=-0.03;
            _bodyguardPosY=-0.1;

            _villain1PosX=-0.8;
            _villain1PosY=.8;
            _villain1X=0;
            _villain1Y=0;

            _villain2PosX=-0.3;
            _villain2PosY=.8;
            _villain2X=0;
            _villain2Y=0;

            _villain3PosX=0.3;
            _villain3PosY=.8;
            _villain3X=0;
            _villain3Y=0;

            _villain4PosX=0.8;
            _villain4PosY=.8;
            _villain4X=0;
            _villain4Y=0;

            score=0;
            level=0;
        }

        break;

    case 32:    ///Space
        if(paused)
        {
            speed = savedSpeed;
            _VillainSpeed = _VillainSavedSpeed;
            paused = false;
        }
        else
        {
            savedSpeed = speed;
            _VillainSavedSpeed = _VillainSpeed;
            paused = true;
        }
        break;
    }
}
/// write score into file
void writeIntoFile()  						//To write high score on to file
{
    FILE *fp = fopen("example.txt","w");
    int i=0;
    char temp[40];
    if(fp!= NULL)
    {
        int n= hscore;
        while(n)
        {
            ch = (n%10)+ '0';
            n/=10;
            temp[i++] = ch;
        }
        temp[i] = '\0';
        strrev(temp);
        puts(temp);
        if(temp[0] == '\0')
            temp[i++] = '0',temp[i++] = '\0';
        fwrite(temp,sizeof(char)*i,i,fp);
    }
    fclose(fp);
}


///Detect Clash
void FindClash()
{
    int vil1X = 700*_villain1X+100000;
    int vil2X = 700*_villain2X+100000;
    int vil3X = 700*_villain3X+100000;
    int vil4X = 700*_villain3X+100000;
    int targetX = 700*_targetPosX+100000;
    int targetY = 700*_targetPosY+100000;
    int bodX = 700*_bodyguardPosX+100000;
    if(_villain1Y <= -0.85078 && _villain1Y >= -1.2 && ((vil1X - bodX) <= 99 &&  (vil1X - bodX) > 56 ))
    {
        _villain1Y = 0.8;
        sndPlaySound(TEXT("F://slap.wav"),SND_ASYNC);
        score=score+5;

    }
    if(_villain2Y <= -0.85078 && _villain2Y >= -1.2 && ((vil2X - bodX) <53 &&  (vil2X - bodX) >=14))
    {
        _villain2Y = 0.8;
        sndPlaySound(TEXT("F://slap.wav"),SND_ASYNC);
        score=score+5;
    }
    if(_villain3Y <= -0.85078 && _villain3Y >= -1.2 && ((vil3X - bodX) <=1 &&  (vil3X - bodX) >-40))
    {
        _villain3Y = 0.8;
        sndPlaySound(TEXT("F://slap.wav"),SND_ASYNC);
        score=score+5;
    }
    if(_villain4Y <= -0.85078 && _villain4Y >= -1.2 && ((vil4X - bodX) <=-42 &&  (vil4X - bodX) >=-83))
    {
        _villain4Y = 0.8;
        sndPlaySound(TEXT("F://slap.wav"),SND_ASYNC);
        score=score+5;
    }

///Level increase
    if(score==40)
    {
        level=1;
    }

    else if(score==60)
    {
        level=2;
    }

    else if(score==100)
    {
        level=3;
    }

    else if(score==130)
    {
        level=4;
    }

    ///Target and villain's Crash
    if(_villain1Y <= -1.202 && _villain1Y >= -1.63418 && ((targetX-vil1X) >= -175 &&  (targetX-vil1X) < -114 ))
    {
        _targetPosX=-999999999990;
        _targetPosY=-9999999999990;

        _bodyguardPosX=-999999999999999990;
        _bodyguardPosY=-999999999999999990;

        _villain1PosX=-99999999999999990;
        _villain1PosY=9999999999999999999;
        _villain1X=9999999999999990;
        _villain1Y=99999999999999999990;

        _villain2PosX=999999999999999990;
        _villain2PosY=9999999999999999;
        _villain2X=999999999999999999999990;
        _villain2Y=999999999999999990;

        _villain3PosX=999999999999999990;
        _villain3PosY=9999999999999999;
        _villain3X=999999999999999999999990;
        _villain3Y=999999999999999990;

        _villain4PosX=999999999999999990;
        _villain4PosY=9999999999999999;
        _villain4X=999999999999999999999990;
        _villain4Y=999999999999999990;
        PlaySound(TEXT("F://maira-dechey.wav"),NULL,SND_ASYNC);
        over = true;

    }

    if(_villain2Y <= -1.202 && _villain2Y >= -1.63418 && ((targetX-vil2X) >= -175 &&  (targetX-vil2X) <= -30 ))
    {
        _targetPosX=-999999999990;
        _targetPosY=-9999999999990;

        _bodyguardPosX=-999999999999999990;
        _bodyguardPosY=-999999999999999990;

        _villain1PosX=-99999999999999990;
        _villain1PosY=9999999999999999999;
        _villain1X=9999999999999990;
        _villain1Y=99999999999999999990;

        _villain2PosX=999999999999999990;
        _villain2PosY=9999999999999999;
        _villain2X=999999999999999999999990;
        _villain2Y=999999999999999990;

        _villain3PosX=999999999999999990;
        _villain3PosY=9999999999999999;
        _villain3X=999999999999999999999990;
        _villain3Y=999999999999999990;

        _villain4PosX=999999999999999990;
        _villain4PosY=9999999999999999;
        _villain4X=999999999999999999999990;
        _villain4Y=999999999999999990;
        PlaySound(TEXT("F://maira-dechey.wav"),NULL,SND_ASYNC);
        over = true;
    }

    if(_villain3Y <= -1.202 && _villain3Y >= -1.63418 && ((targetX-vil3X) >= -84 &&  (targetX-vil3X) <= 35 ))
    {
        _targetPosX=-999999999990;
        _targetPosY=-9999999999990;

        _bodyguardPosX=-999999999999999990;
        _bodyguardPosY=-999999999999999990;

        _villain1PosX=-99999999999999990;
        _villain1PosY=9999999999999999999;
        _villain1X=9999999999999990;
        _villain1Y=99999999999999999990;

        _villain3PosX=999999999999999990;
        _villain3PosY=9999999999999999;
        _villain3X=999999999999999999999990;
        _villain3Y=999999999999999990;

        _villain2PosX=999999999999999990;
        _villain2PosY=9999999999999999;
        _villain2X=999999999999999999999990;
        _villain2Y=999999999999999990;

        _villain4PosX=999999999999999990;
        _villain4PosY=9999999999999999;
        _villain4X=999999999999999999999990;
        _villain4Y=999999999999999990;
        PlaySound(TEXT("F://maira-dechey.wav"),NULL,SND_ASYNC);
        over = true;

    }

    if(_villain4Y <= -1.202 && _villain4Y >= -1.63418 && ((targetX-vil4X) >= -1 &&  (targetX-vil4X) <= 35 ))
    {
        _targetPosX=-999999999990;
        _targetPosY=-9999999999990;

        _bodyguardPosX=-999999999999999990;
        _bodyguardPosY=-999999999999999990;

        _villain1PosX=-99999999999999990;
        _villain1PosY=9999999999999999999;
        _villain1X=9999999999999990;
        _villain1Y=99999999999999999990;

        _villain3PosX=999999999999999990;
        _villain3PosY=9999999999999999.8;
        _villain3X=999999999999999999999990;
        _villain3Y=999999999999999990;

        _villain2PosX=999999999999999990;
        _villain2PosY=9999999999999999;
        _villain2X=999999999999999999999990;
        _villain2Y=999999999999999990;

        _villain4PosX=999999999999999990;
        _villain4PosY=9999999999999999;
        _villain4X=999999999999999999999990;
        _villain4Y=999999999999999990;
        PlaySound(TEXT("F://maira-dechey.wav"),NULL,SND_ASYNC);
        over = true;

    }
///Score decrease
    if(_villain1Y <= -1.7)
    {
        _villain1Y = 0.8;
        score-=5;
    }
    if(_villain2Y <= -1.7)
    {
        _villain2Y = 0.8;
        score-=5;
    }
    if(_villain3Y <= -1.7)
    {
        _villain3Y = 0.8;
        score-=5;
    }
    if(_villain4Y <= -1.7)
    {
        _villain4Y = 0.8;
        score-=5;
    }

}

int main(int argc, char** argv)
{
    string line;            ///read from file
    ifstream myfile ("example.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            stringstream geek(line);
            geek >> hscore;
        }
        myfile.close();
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);

    ///Create the window
    glutCreateWindow("Bodyguard");

    ///Set handler functions
    glutDisplayFunc(drawScene);

    glutSpecialFunc(specialKeys); //Special Key Handler
    glutKeyboardFunc(keyboard);   //Basic keyboard key handler


    glutTimerFunc(25, update, 0); //Add a timer
    glutTimerFunc(25, villainUpdate, 0); //Add a timer
    glutMainLoop();
    return 0;
}
