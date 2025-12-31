#define STB_IMAGE_IMPLEMENTATION
#include "func.h"
#include "stb_image.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int currentMeshNum;
extern int currentAnimNum;
extern int mainloopcount;
extern int key1;
extern int key2;
extern SDL_Window* window;

obj loadingmesh;
obj loadinganim;
obj back[25];
obj dash[16];
obj forward[26];
obj Idle[75];
obj jump[41];
obj left[22];
obj right[22];

obj aincradIMAGE;
obj raceIMAGE;
obj chessIMAGE;
obj shootingIMAGE;
obj tankIMAGE;
obj parkIMAGE;

cheapObj num_0;
cheapObj num_1;
cheapObj num_2;
cheapObj num_3;
cheapObj num_4;
cheapObj num_5;
cheapObj num_6;
cheapObj num_7;
cheapObj num_8;
cheapObj num_9;
extern cheapObj chess_circle;
extern cheapObj chess_P;
extern cheapObj chess_R;
extern cheapObj chess_B;
extern cheapObj chess_N;
extern cheapObj chess_Q;
extern cheapObj chess_K;
extern cheapObj chess_masu;

extern float diffuseMat[];
extern float specularMat[];
extern float ambientMat[];
extern float lightposMat[];
extern float elapsedSeconds;


GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // �e�N�X�`���p�����[�^�̐ݒ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        // �e�N�X�`���摜���o�C���h����
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // �蓮�Ń~�b�v�}�b�v�𐶐�����
        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void makeLoadingCount(int objcount)
{
    int a1, a2, a3;
    int b1, b2, b3;

    a3 = currentMeshNum / 100;
    a2 = (currentMeshNum % 100) / 10;
    a1 = currentMeshNum % 10;
    b3 = objcount / 100;
    b2 = (objcount % 100) / 10;
    b1 = objcount % 10;

    float es = std::fmod(elapsedSeconds, 60.0f);
    if (mainloopcount == 0 || mainloopcount == 1)
    {
        if (es > 0.0f && es < 10.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
			glRotatef(180, 0, 0, 1);
            aincradIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();
        }
        else if (es > 10.0f && es < 20.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            parkIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 20.0f && es < 30.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            chessIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 30.0f && es < 40.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            tankIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 40.0f && es < 50.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            raceIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 50.0f && es < 60.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            shootingIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
    }
    else if(mainloopcount == 2)//return park
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        parkIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }
    else if(mainloopcount == 3)//race
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        raceIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }
    else if(mainloopcount == 4)//chess
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        chessIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }
    else if(mainloopcount == 5)//shooting
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        shootingIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }
    else if(mainloopcount == 6)//tank
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        tankIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0.11, -0.050916 , -0.03519);
    switch (a3)
    {
    case 0:
        num_0.make(1.0f,1.0f,1.0f);
        break;
    case 1:
        num_1.make(1.0f,1.0f,1.0f);
        break;
    case 2:
        num_2.make(1.0f,1.0f,1.0f);
        break;
    case 3:
        num_3.make(1.0f,1.0f,1.0f);
        break;
    case 4:
        num_4.make(1.0f,1.0f,1.0f);
        break;
    case 5:
        num_5.make(1.0f,1.0f,1.0f);
        break;
    case 6:
        num_6.make(1.0f,1.0f,1.0f);
        break;
    case 7:
        num_7.make(1.0f,1.0f,1.0f);
        break;
    case 8:
        num_8.make(1.0f,1.0f,1.0f);
        break;
    case 9:
        num_9.make(1.0f,1.0f,1.0f);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.058596 , -0.03519);
    switch (a2)
    {
    case 0:
        num_0.make(1.0f,1.0f,1.0f);
        break;
    case 1:
        num_1.make(1.0f,1.0f,1.0f);
        break;
    case 2:
        num_2.make(1.0f,1.0f,1.0f);
        break;
    case 3:
        num_3.make(1.0f,1.0f,1.0f);
        break;
    case 4:
        num_4.make(1.0f,1.0f,1.0f);
        break;
    case 5:
        num_5.make(1.0f,1.0f,1.0f);
        break;
    case 6:
        num_6.make(1.0f,1.0f,1.0f);
        break;
    case 7:
        num_7.make(1.0f,1.0f,1.0f);
        break;
    case 8:
        num_8.make(1.0f,1.0f,1.0f);
        break;
    case 9:
        num_9.make(1.0f,1.0f,1.0f);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.066276 , -0.03519);
    switch (a1)
    {
    case 0:
        num_0.make(1.0f,1.0f,1.0f);
        break;
    case 1:
        num_1.make(1.0f,1.0f,1.0f);
        break;
    case 2:
        num_2.make(1.0f,1.0f,1.0f);
        break;
    case 3:
        num_3.make(1.0f,1.0f,1.0f);
        break;
    case 4:
        num_4.make(1.0f,1.0f,1.0f);
        break;
    case 5:
        num_5.make(1.0f,1.0f,1.0f);
        break;
    case 6:
        num_6.make(1.0f,1.0f,1.0f);
        break;
    case 7:
        num_7.make(1.0f,1.0f,1.0f);
        break;
    case 8:
        num_8.make(1.0f,1.0f,1.0f);
        break;
    case 9:
        num_9.make(1.0f,1.0f,1.0f);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.080247 , -0.03519);
    switch (b3)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.08781 , -0.03519);
    switch (b2)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.095479 , -0.03519);
    switch (b1)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();
}

void makeLoadingCount(int current,int max)
{
    int a1, a2, a3;
    int b1, b2, b3;

    a3 = current / 100;
    a2 = (current % 100) / 10;
    a1 = current % 10;
    b3 = max / 100;
    b2 = (max % 100) / 10;
    b1 = max % 10;

    if (mainloopcount == 0 || mainloopcount == 1)
    {
		float es = std::fmod(elapsedSeconds, 60.0f);
        if (es > 0.0f && es < 10.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
			glRotatef(180, 0, 0, 1);
            aincradIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();
        }
        else if (es > 10.0f && es < 20.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            parkIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 20.0f && es < 30.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            chessIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 30.0f && es < 40.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            tankIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 40.0f && es < 50.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            raceIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
        else if (es > 50.0f && es < 60.0f)
        {
            glPushMatrix();
            glTranslatef(0.112, 0, 0);
            glRotatef(180, 0, 0, 1);

            shootingIMAGE.makeWithTex(1, 1, 1);
            glPopMatrix();

        }
    }
    else if(mainloopcount == 3)
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        raceIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();        
    }
    else if(mainloopcount ==4)
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        chessIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }
    else if(mainloopcount == 5)
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        shootingIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    } 
    else if(mainloopcount == 6 )
    {
        glPushMatrix();
        glTranslatef(0.112, 0, 0);
        glRotatef(180, 0, 0, 1);

        tankIMAGE.makeWithTex(1, 1, 1);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0.11, -0.050916 , -0.03519);
    switch (a3)
    {
    case 0:
        num_0.make(1,1,1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.058596 , -0.03519);
    switch (a2)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.066276 , -0.03519);
    switch (a1)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.080247 , -0.03519);
    switch (b3)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.08781 , -0.03519);
    switch (b2)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, -0.095479 , -0.03519);
    switch (b1)
    {
    case 0:
        num_0.make(1, 1, 1);
        break;
    case 1:
        num_1.make(1, 1, 1);
        break;
    case 2:
        num_2.make(1, 1, 1);
        break;
    case 3:
        num_3.make(1, 1, 1);
        break;
    case 4:
        num_4.make(1, 1, 1);
        break;
    case 5:
        num_5.make(1, 1, 1);
        break;
    case 6:
        num_6.make(1, 1, 1);
        break;
    case 7:
        num_7.make(1, 1, 1);
        break;
    case 8:
        num_8.make(1, 1, 1);
        break;
    case 9:
        num_9.make(1, 1, 1);
        break;
    }
    glPopMatrix();
}

void obj::load(const char* mesh,int loadingCount)
{
    Data = fopen(mesh, "r");
    //fopen_s(&Data, mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n",mesh);
        currentMeshNum++;
        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }
    currentMeshNum++;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.11, 0, 0);
    loadingmesh.make(1, 1, 1);
    glPopMatrix();

    makeLoadingCount(loadingCount);
}

void obj::load(const char* mesh , bool f)
{
    if (f == false)
        return;
    Data = fopen(mesh, "r");
    //fopen_s(&Data, mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n",mesh);
        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }
}

void obj::load(const char* mesh, const char* texture,int loadingCount)
{
    //fopen_s(&Data, mesh, "r");
    Data = fopen(mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n", mesh);
        currentMeshNum++;

        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    setupVBO();

    currentMeshNum++;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.11, 0, 0);
    loadingmesh.make(1,1,1);
    glPopMatrix();

    makeLoadingCount(loadingCount);
}

void obj::load(const char* mesh, const char* texture)
{
    //fopen_s(&Data, mesh, "r");
    Data = fopen(mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n", mesh);
        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    setupVBO();
}
void obj::makeWithTex(float r, float g, float b)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER,vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0,vertex.size() / 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void obj::makeWithTex_Color(float r, float g, float b)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER,vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0,vertex.size() / 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void obj::make(float r, float g, float b)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glNormalPointer(GL_FLOAT, 0, flat.data());
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void obj::make_Color(float r, float g, float b)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glNormalPointer(GL_FLOAT, 0, flat.data());
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}

void obj::setupVBO()
{
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, flat.size() * sizeof(GLfloat), flat.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(GLfloat), UV.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SafeDeleteBuffer(GLuint& bufferID) {
    if (bufferID != 0) {
        glDeleteBuffers(1, &bufferID);
        bufferID = 0;
    }
}

void obj::Uninit()
{
    if (Data != NULL) {
        fclose(Data);
        Data = NULL;
    }
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    SafeDeleteBuffer(vertexVBO);
    SafeDeleteBuffer(normalVBO);
    SafeDeleteBuffer(uvVBO);
    vertex.clear();
    vertex.shrink_to_fit();
    flat.clear();
    flat.shrink_to_fit();
    UV.clear();
    UV.shrink_to_fit();
    vertexDataSize = 0;
    flatDataSize = 0;
    UVDataSize = 0;
}

void cheapObj::load(const char* mesh,int loadingCount)
{
    //fopen_s(&Data, mesh, "r");
    Data = fopen(mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n",mesh);
        currentMeshNum++;

        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }

    currentMeshNum++;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.11, 0, 0);
    loadingmesh.make(1.0f,1.0f,1.0f);
    glPopMatrix();

    makeLoadingCount(loadingCount);

}

void cheapObj::load(const char* mesh, bool f)
{
    if (f == false)
        return;
    //fopen_s(&Data, mesh, "r");
    Data = fopen(mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n",mesh);
        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }
}

void cheapObj::load(const char* mesh, const char* texture,int loadingCount)
{
    //fopen_s(&Data, mesh, "r");
    Data = fopen(mesh, "r");
    if (Data == NULL)
    {
        printf("%s roading error\n", mesh);
        currentMeshNum++;

        return;
    }
    else
    {
        printf("success!!\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            switch (c)
            {
            case 'v':
                vertex.push_back(x);
                vertex.push_back(y);
                vertex.push_back(z);
                vertexDataSize++;
                break;
            case 'u':
                UV.push_back(x);
                UV.push_back(y);
                UVDataSize++;
                break;
            case 'n':
                flat.push_back(x);
                flat.push_back(y);
                flat.push_back(z);
                flatDataSize++;
                break;
            default:
                break;
            }
        }
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);


    currentMeshNum++;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.11, 0, 0);
    loadingmesh.make(1.0f,1.0f,1.0f);
    glPopMatrix();

    makeLoadingCount(loadingCount);
}

void cheapObj::Uninit()
{
    if (Data != NULL) {
        fclose(Data);
        Data = NULL;
    }
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    vertex.clear();
    vertex.shrink_to_fit();
    flat.clear();
    flat.shrink_to_fit();
    UV.clear();
    UV.shrink_to_fit();
    vertexDataSize = 0;
    flatDataSize = 0;
    UVDataSize = 0;
}

void cheapObj::makeWithBlend(float r, float g, float b,float angle)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glColor3f(r, g, b);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, sinf(angle * PI / 180.0));

    glDrawArrays(GL_TRIANGLES, 0, vertex.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}

void cheapObj::make(float r, float g, float b)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glNormalPointer(GL_FLOAT, 0, flat.data());
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void cheapObj::make_Color(float r, float g, float b)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

float cul2PointDistance(float x1,float y1,float x2,float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void makeChess_2D_icon(int map[8][8], chess_stts stts, int index_tate, int index_yoko, int myColor, int cursorX, int cursorY, float displayX, float displayY, float displayW, float colorSita, chess_info ci, chess_kind_piece cp)
{
    if (stts == get_piece)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                switch (map[i][j])
                {
                case 1://WP
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0.8, 0.8, 1);
                    chess_P.make_Color(0, 0, 0);
                    if(key1 == 1 && myColor == 0)
                    {
                        chess_masu.make(1,1,0);
                    }
                    glPopMatrix();
                    break;
                case 2://WR
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0.8, 0.8, 1);
                    chess_R.make_Color(0, 0, 0);
                    if(key1 == 2 && myColor == 0)
                    {
                        chess_masu.make(1,1,0);
                    }                    
                    glPopMatrix();
                    break;
                case 3://WN
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0.8, 0.8, 1);
                    chess_N.make_Color(0, 0, 0);
                    if(key1 == 3 && myColor == 0)
                    {
                        chess_masu.make(1,1,0);
                    }   
                    glPopMatrix();
                    break;
                case 4://WB
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0.8, 0.8, 1);
                    chess_B.make_Color(0, 0, 0);
                    if(key1 == 4 && myColor == 0)
                    {
                        chess_masu.make(1,1,0);
                    }   
                    glPopMatrix();
                    break;
                case 5://WK
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0.8, 0.8, 1);
                    chess_K.make_Color(0, 0, 0);
                    if(key1 == 5 && myColor == 0)
                    {
                        chess_masu.make(1,1,0);
                    }                      
                    glPopMatrix();
                    break;
                case 6://WQ
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0.8, 0.8, 1);
                    chess_Q.make_Color(0, 0, 0);
                    if(key1 == 6 && myColor == 0)
                    {
                        chess_masu.make(1,1,0);
                    }                      
                    glPopMatrix();
                    break;
                case 7://BP
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0, 0, 0.2);
                    chess_P.make_Color(1,1,1);
                    if(key2 == 7 && myColor == 1)
                    {
                        chess_masu.make(1,1,0);
                    }                      
                    glPopMatrix();
                    break;
                case 8://BR
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0, 0, 0.2);
                    chess_R.make_Color(1,1,1);
                    if(key2 == 8 && myColor == 1)
                    {
                        chess_masu.make(1,1,0);
                    }                        
                    glPopMatrix();
                    break;
                case 9://BN
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0, 0, 0.2);
                    chess_N.make_Color(1,1,1);
                    if(key2 == 9 && myColor == 1)
                    {
                        chess_masu.make(1,1,0);
                    }                        
                    glPopMatrix();
                    break;
                case 10://BB
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0, 0, 0.2);
                    chess_B.make_Color(1,1,1);
                    if(key2 == 10 && myColor == 1)
                    {
                        chess_masu.make(1,1,0);
                    }                        
                    glPopMatrix();
                    break;
                case 11://BK
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0, 0, 0.2);
                    chess_K.make_Color(1,1,1);
                    if(key2 == 11 && myColor == 1)
                    {
                        chess_masu.make(1,1,0);
                    }                        
                    glPopMatrix();
                    break;
                case 12://BQ
                    glPushMatrix();
                    glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                    chess_circle.make_Color(0, 0, 0.2);
                    chess_Q.make_Color(1,1,1);
                    if(key2 == 12 && myColor == 1)
                    {
                        chess_masu.make(1,1,0);
                    }                        
                    glPopMatrix();
                    break;
                default:
                    break;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                switch (map[i][j])
                {
                case 1://���|�[��
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0.8, 0.8,1);
                        chess_P.make_Color(0, 0, 0);
                        glPopMatrix();

                        switch (cp)
                        {
                        case bp1:
                            if (ci.bp1.pos[0] == 6 && map[i-2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if(map[i-1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i-1 >= 0 && j-1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case bp2:
                            if (ci.bp2.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case bp3:
                            if (ci.bp3.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }

                            break;
                        case bp4:
                            if (ci.bp4.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }

                            break;
                        case bp5:
                            if (ci.bp5.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case bp6:
                            if (ci.bp6.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case bp7:
                            if (ci.bp7.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case bp8:
                            if (ci.bp8.pos[0] == 6 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_P.make_Color(0, 0, 0);
                        glPopMatrix();
                    }
                    break;
                case 2://�����[�N
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_R.make_Color(0,0,0);
                        glPopMatrix();

                        //�O����
                        int fore;
                        for (fore = 0; fore < 8; fore++)
                        {
                            if (map[i - 1 - fore][j] != 0 || i - 1 - fore < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - fore][j] >= 7 && map[i - 1 - fore][j] <= 12 && i - 1 - fore >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�����
                        int behi;
                        for (behi = 0; behi < 8; behi++)
                        {
                            if (map[i + 1 + behi][j] != 0 || i + 1 + behi >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + behi][j] >= 7 && map[i + 1 + behi][j] <= 12 && i + 1 + behi >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //������
                        int left;
                        for (left = 0; left < 8; left++)
                        {
                            if (map[i][j - 1 - left] != 0 || j - 1 - left < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j - 1 - left] >= 7 && map[i][j - 1 - left] <= 12 && j - 1 - left >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i ));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E����
                        int right;
                        for (right = 0; right < 8; right++)
                        {
                            if (map[i][j + 1 + right] != 0 || j + 1 + right >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j + 1 + right] >= 7 && map[i][j + 1 + right] <= 12 && j + 1 + right >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }


                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_R.make_Color(0,0,0);
                        glPopMatrix();
                    }
                    break;
                case 3://���i�C�g
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_N.make_Color(0,0,0);
                        glPopMatrix();

                        //�i�C�g�̎���8�ӏ��̏ꏊ�𒲂ׂ�
                        if ((map[i - 2][j + 1] == 0 || (map[i - 2][j + 1] >= 7 && map[i - 2][j + 1] <= 12)) && i - 2 >= 0 && j + 1 <= 7)//�E���
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j + 2] == 0 || (map[i - 1][j + 2] >= 7 && map[i - 1][j + 2] <= 12)) && i - 1 >= 0 && j + 2 <= 7)//�E��E
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 2)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 2][j + 1] == 0 || (map[i + 2][j + 1] >= 7 && map[i + 2][j + 1] <= 12)) && i + 2 <= 7 && j+ 1 <= 7)//�E����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i + 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j + 2] == 0 || (map[i + 1][j + 2] >= 7 && map[i + 1][j + 2] <= 12)) && i + 1 <= 7 && j + 2 <= 7)//�E���E
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 2)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 2][j - 1] == 0 || (map[i - 2][j - 1] >= 7 && map[i - 2][j - 1] <= 12)) && i-2 >= 0 && j - 1 >= 0)//�����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j - 2] == 0 || (map[i - 1][j - 2] >= 7 && map[i - 1][j - 2] <= 12)) && i - 1 >= 0 && j - 2 >= 0)//���㍶
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 2)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 2][j - 1] == 0 || (map[i + 2][j - 1] >= 7 && map[i + 2][j - 1] <= 12)) && i + 2 <= 7 && j- 1 >= 0)//������
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i + 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j - 2] == 0 || (map[i + 1][j - 2] >= 7 && map[i + 1][j - 2] <= 12)) && i + 1 <= 7 && j - 2  >= 0)//������
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 2)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_N.make_Color(0,0,0);
                        glPopMatrix();
                    }
                    break;
                case 4://���r�V���b�v
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_B.make_Color(0,0,0);
                        glPopMatrix();

                        //����
                        int leftUp;
                        for (leftUp = 0; leftUp < 8; leftUp++)
                        {
                            if (map[i - 1 - leftUp][j - 1 - leftUp] != 0 || i - 1 - leftUp < 0 || j - 1 - leftUp < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - leftUp][j - 1 - leftUp] >= 7 && map[i - 1 - leftUp][j - 1 - leftUp] <= 12 && i - 1 - leftUp >= 0 && j - 1 - leftUp >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightUp;
                        for (rightUp = 0; rightUp < 8; rightUp++)
                        {
                            if (map[i - 1 - rightUp][j + 1 + rightUp] != 0 || i - 1 - rightUp < 0 || j + 1 + rightUp > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - rightUp][j + 1 + rightUp] >= 7 && map[i - 1 - rightUp][j + 1 + rightUp] <= 12 && i - 1 - rightUp >= 0 && j + 1 + rightUp <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightDown;
                        for (rightDown = 0; rightDown < 8; rightDown++)
                        {
                            if (map[i + 1 + rightDown][j + 1 + rightDown] != 0 || i + 1 + rightDown > 7 || j + 1 + rightDown > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + rightDown][j + 1 + rightDown] >= 7 && map[i + 1 + rightDown][j + 1 + rightDown] <= 12 && i + 1 + rightDown <= 7 && j + 1 + rightDown <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //����
                        int leftDown;
                        for (leftDown = 0; leftDown < 8; leftDown++)
                        {
                            if (map[i + 1 + leftDown][j - 1 - leftDown] != 0 || i + 1 + leftDown > 7 || j - 1 - leftDown < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + leftDown][j - 1 - leftDown] >= 7 && map[i + 1 + leftDown][j - 1 - leftDown] <= 12 && i + 1 + leftDown <= 7 && j - 1 - leftDown >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_B.make_Color(0,0,0);
                        glPopMatrix();
                    }
                    break;
                case 5://���L���O
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_K.make_Color(0,0,0);
                        glPopMatrix();

                        if ((map[i - 1][j + 1] == 0 || (map[i - 1][j + 1] >= 7 && map[i - 1][j + 1] <= 12)) && i - 1 >= 0 && j + 1 <= 7)//�E��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i][j + 1] == 0 || (map[i][j + 1] >= 7 && map[i][j + 1] <= 12)) && j + 1 <= 7)//�E
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j + 1] == 0 || (map[i + 1][j + 1] >= 7 && map[i + 1][j + 1] <= 12)) && i + 1 <= 7 && j + 1 <= 7)//�E��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j] == 0 || (map[i + 1][j] >= 7 && map[i + 1][j] <= 12)) && i + 1 <= 7)//��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j - 1] == 0 || (map[i + 1][j - 1] >= 7 && map[i + 1][j - 1] <= 12)) && i + 1 <= 7 && j - 1 >= 0)//����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i][j - 1] == 0 || (map[i][j - 1] >= 7 && map[i][j - 1] <= 12)) && j - 1 >= 0)//��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * i ));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j - 1] == 0 || (map[i - 1][j - 1] >= 7 && map[i - 1][j - 1] <= 12)) && i - 1 >= 0 && j - 1 >= 0)//����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j] == 0 || (map[i - 1][j] >= 7 && map[i - 1][j] <= 12)) && i - 1 >= 0)//��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j ), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_K.make_Color(0,0,0);
                        glPopMatrix();
                    }
                    break;
                case 6://���N�C�[��
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_Q.make_Color(0,0,0);
                        glPopMatrix();

                        //����
                        int leftUp;
                        for (leftUp = 0; leftUp < 8; leftUp++)
                        {
                            if (map[i - 1 - leftUp][j - 1 - leftUp] != 0 || i - 1 - leftUp < 0 || j - 1 - leftUp < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - leftUp][j - 1 - leftUp] >= 7 && map[i - 1 - leftUp][j - 1 - leftUp] <= 12 && i - 1 - leftUp >= 0 && j - 1 - leftUp >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightUp;
                        for (rightUp = 0; rightUp < 8; rightUp++)
                        {
                            if (map[i - 1 - rightUp][j + 1 + rightUp] != 0 || i - 1 - rightUp < 0 || j + 1 + rightUp > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - rightUp][j + 1 + rightUp] >= 7 && map[i - 1 - rightUp][j + 1 + rightUp] <= 12 && i - 1 - rightUp >= 0 && j + 1 + rightUp <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightDown;
                        for (rightDown = 0; rightDown < 8; rightDown++)
                        {
                            if (map[i + 1 + rightDown][j + 1 + rightDown] != 0 || i + 1 + rightDown > 7 || j + 1 + rightDown > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + rightDown][j + 1 + rightDown] >= 7 && map[i + 1 + rightDown][j + 1 + rightDown] <= 12 && i + 1 + rightDown <= 7 && j + 1 + rightDown <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //����
                        int leftDown;
                        for (leftDown = 0; leftDown < 8; leftDown++)
                        {
                            if (map[i + 1 + leftDown][j - 1 - leftDown] != 0 || i + 1 + leftDown > 7 || j - 1 - leftDown < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + leftDown][j - 1 - leftDown] >= 7 && map[i + 1 + leftDown][j - 1 - leftDown] <= 12 && i + 1 + leftDown <= 7 && j - 1 - leftDown >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�O����
                        int fore;
                        for (fore = 0; fore < 8; fore++)
                        {
                            if (map[i - 1 - fore][j] != 0 || i - 1 - fore < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - fore][j] >= 7 && map[i - 1 - fore][j] <= 12 && i - 1 - fore >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�����
                        int behi;
                        for (behi = 0; behi < 8; behi++)
                        {
                            if (map[i + 1 + behi][j] != 0 || i + 1 + behi >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + behi][j] >= 7 && map[i + 1 + behi][j] <= 12 && i + 1 + behi >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //������
                        int left;
                        for (left = 0; left < 8; left++)
                        {
                            if (map[i][j - 1 - left] != 0 || j - 1 - left < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j - 1 - left] >= 7 && map[i][j - 1 - left] <= 12 && j - 1 - left >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E����
                        int right;
                        for (right = 0; right < 8; right++)
                        {
                            if (map[i][j + 1 + right] != 0 || j + 1 + right >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j + 1 + right] >= 7 && map[i][j + 1 + right] <= 12 && j + 1 + right >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0.8, 0.8, 1);
                        chess_Q.make_Color(0,0,0);
                        glPopMatrix();
                    }
                    break;
                case 7: //���|�[��
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_P.make_Color(1, 1, 1);
                        glPopMatrix();

                        switch (cp)
                        {
                        case wp1:
                            if (ci.wp1.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case wp2:
                            if (ci.wp2.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case wp3:
                            if (ci.wp3.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }

                            break;
                        case wp4:
                            if (ci.wp4.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }

                            break;
                        case wp5:
                            if (ci.wp5.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case wp6:
                            if (ci.wp6.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case wp7:
                            if (ci.wp7.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        case wp8:
                            if (ci.wp8.pos[0] == 1 && map[i - 2][j] == 0)
                            {
                                //�O2��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 2)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();

                            }
                            else if (map[i - 1][j] == 0)
                            {
                                //�O1��
                                glPushMatrix();
                                glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                                chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                glPopMatrix();
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//���΂ߑO[i-1][j-1]
                            {
                                if (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            if (i - 1 >= 0 && j + 1 <= 7)//�E�΂ߑO[i-1][j+1]
                            {
                                if (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)
                                {
                                    glPushMatrix();
                                    glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                                    chess_masu.makeWithBlend(1, 0, 0, colorSita);
                                    glPopMatrix();
                                }
                            }
                            break;
                        default:
                            break;
                        }

                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_P.make_Color(1, 1, 1);
                        glPopMatrix();
                    }
                    break;
                case 8://�����[�N
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_R.make_Color(1, 1, 1);
                        glPopMatrix();

                        //�O����
                        int fore;
                        for (fore = 0; fore < 8; fore++)
                        {
                            if (map[i - 1 - fore][j] != 0 || i - 1 - fore < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - fore][j] >= 1 && map[i - 1 - fore][j] <= 6 && i - 1 - fore >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�����
                        int behi;
                        for (behi = 0; behi < 8; behi++)
                        {
                            if (map[i + 1 + behi][j] != 0 || i + 1 + behi >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + behi][j] >= 1 && map[i + 1 + behi][j] <= 6 && i + 1 + behi >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //������
                        int left;
                        for (left = 0; left < 8; left++)
                        {
                            if (map[i][j - 1 - left] != 0 || j - 1 - left < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j - 1 - left] >= 1 && map[i][j - 1 - left] <= 6 && j - 1 - left >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E����
                        int right;
                        for (right = 0; right < 8; right++)
                        {
                            if (map[i][j + 1 + right] != 0 || j + 1 + right >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j + 1 + right] >= 1 && map[i][j + 1 + right] <= 6 && j + 1 + right >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_R.make_Color(1, 1, 1);
                        glPopMatrix();
                    }
                    break;
                case 9://���i�C�g
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_N.make_Color(1, 1, 1);
                        glPopMatrix();

                        if ((map[i - 2][j + 1] == 0 || (map[i - 2][j + 1] >= 1 && map[i - 2][j + 1] <= 6)) && i - 2 >= 0 && j + 1 <= 7)//�E���
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j + 2] == 0 || (map[i - 1][j + 2] >= 1 && map[i - 1][j + 2] <= 6)) && i - 1 >= 0 && j + 2 <= 7)//�E��E
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 2)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 2][j + 1] == 0 || (map[i + 2][j + 1] >= 1 && map[i + 2][j + 1] <= 6)) && i + 2 <= 7 && j + 1 <= 7)//�E����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i + 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j + 2] == 0 || (map[i + 1][j + 2] >= 1 && map[i + 1][j + 2] <= 6)) && i + 1 <= 7 && j + 2 <= 7)//�E���E
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 2)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 2][j - 1] == 0 || (map[i - 2][j - 1] >= 1 && map[i - 2][j - 1] <= 6)) && i - 2 >= 0 && j - 1 >= 0)//�����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j - 2] == 0 || (map[i - 1][j - 2] >= 1 && map[i - 1][j - 2] <= 6)) && i - 1 >= 0 && j - 2 >= 0)//���㍶
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 2)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 2][j - 1] == 0 || (map[i + 2][j - 1] >= 1 && map[i + 2][j - 1] <= 6)) && i + 2 <= 7 && j - 1 >= 0)//������
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i + 2)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j - 2] == 0 || (map[i + 1][j - 2] >= 1 && map[i + 1][j - 2] <= 6)) && i + 1 <= 7 && j - 2 >= 0)//������
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 2)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_N.make_Color(1, 1, 1);
                        glPopMatrix();
                    }
                    break;
                case 10://���r�V���b�v
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_B.make_Color(1, 1, 1);
                        glPopMatrix();

                        //����
                        int leftUp;
                        for (leftUp = 0; leftUp < 8; leftUp++)
                        {
                            if (map[i - 1 - leftUp][j - 1 - leftUp] != 0 || i - 1 - leftUp < 0 || j - 1 - leftUp < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - leftUp][j - 1 - leftUp] >= 1 && map[i - 1 - leftUp][j - 1 - leftUp] <= 6 && i - 1 - leftUp >= 0 && j - 1 - leftUp >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightUp;
                        for (rightUp = 0; rightUp < 8; rightUp++)
                        {
                            if (map[i - 1 - rightUp][j + 1 + rightUp] != 0 || i - 1 - rightUp < 0 || j + 1 + rightUp > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - rightUp][j + 1 + rightUp] >= 1 && map[i - 1 - rightUp][j + 1 + rightUp] <= 6 && i - 1 - rightUp >= 0 && j + 1 + rightUp <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightDown;
                        for (rightDown = 0; rightDown < 8; rightDown++)
                        {
                            if (map[i + 1 + rightDown][j + 1 + rightDown] != 0 || i + 1 + rightDown > 7 || j + 1 + rightDown > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + rightDown][j + 1 + rightDown] >= 1 && map[i + 1 + rightDown][j + 1 + rightDown] <= 6 && i + 1 + rightDown <= 7 && j + 1 + rightDown <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //����
                        int leftDown;
                        for (leftDown = 0; leftDown < 8; leftDown++)
                        {
                            if (map[i + 1 + leftDown][j - 1 - leftDown] != 0 || i + 1 + leftDown > 7 || j - 1 - leftDown < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + leftDown][j - 1 - leftDown] >= 1 && map[i + 1 + leftDown][j - 1 - leftDown] <= 6 && i + 1 + leftDown <= 7 && j - 1 - leftDown >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }


                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_B.make_Color(1, 1, 1);
                        glPopMatrix();
                    }
                    break;
                case 11://���L���O
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_K.make_Color(1, 1, 1);
                        glPopMatrix();

                        if ((map[i - 1][j + 1] == 0 || (map[i - 1][j + 1] >= 1 && map[i - 1][j + 1] <= 6)) && i - 1 >= 0 && j + 1 <= 7)//�E��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i][j + 1] == 0 || (map[i][j + 1] >= 1 && map[i][j + 1] <= 6)) && j + 1 <= 7)//�E
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j + 1] == 0 || (map[i + 1][j + 1] >= 1 && map[i + 1][j + 1] <= 6)) && i + 1 <= 7 && j + 1 <= 7)//�E��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j] == 0 || (map[i + 1][j] >= 1 && map[i + 1][j] <= 6)) && i + 1 <= 7)//��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i + 1][j - 1] == 0 || (map[i + 1][j - 1] >= 1 && map[i + 1][j - 1] <= 6)) && i + 1 <= 7 && j - 1 >= 0)//����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i + 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i][j - 1] == 0 || (map[i][j - 1] >= 1 && map[i][j - 1] <= 6)) && j - 1 >= 0)//��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j - 1] == 0 || (map[i - 1][j - 1] >= 1 && map[i - 1][j - 1] <= 6)) && i - 1 >= 0 && j - 1 >= 0)//����
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1)), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if ((map[i - 1][j] == 0 || (map[i - 1][j] >= 1 && map[i - 1][j] <= 6)) && i - 1 >= 0)//��
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }


                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_K.make_Color(1, 1, 1);
                        glPopMatrix();
                    }
                    break;
                case 12://���N�C�[��
                    if (i == index_tate && j == index_yoko)
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - ((cursorX - displayX) * (world_chess_size / (displayW + 1.0))) + tyousei, chess_map_y - ((cursorY - displayY) * (world_chess_size / displayW)) + tyousei);
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_Q.make_Color(1, 1, 1);
                        glPopMatrix();

                        //����
                        int leftUp;
                        for (leftUp = 0; leftUp < 8; leftUp++)
                        {
                            if (map[i - 1 - leftUp][j - 1 - leftUp] != 0 || i - 1 - leftUp < 0 || j - 1 - leftUp < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - leftUp][j - 1 - leftUp] >= 1 && map[i - 1 - leftUp][j - 1 - leftUp] <= 6 && i - 1 - leftUp >= 0 && j - 1 - leftUp >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftUp)), chess_map_y - (world_chess_size * (i - 1 - leftUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightUp;
                        for (rightUp = 0; rightUp < 8; rightUp++)
                        {
                            if (map[i - 1 - rightUp][j + 1 + rightUp] != 0 || i - 1 - rightUp < 0 || j + 1 + rightUp > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - rightUp][j + 1 + rightUp] >= 1 && map[i - 1 - rightUp][j + 1 + rightUp] <= 6 && i - 1 - rightUp >= 0 && j + 1 + rightUp <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightUp)), chess_map_y - (world_chess_size * (i - 1 - rightUp)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E��
                        int rightDown;
                        for (rightDown = 0; rightDown < 8; rightDown++)
                        {
                            if (map[i + 1 + rightDown][j + 1 + rightDown] != 0 || i + 1 + rightDown > 7 || j + 1 + rightDown > 7)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + rightDown][j + 1 + rightDown] >= 1 && map[i + 1 + rightDown][j + 1 + rightDown] <= 6 && i + 1 + rightDown <= 7 && j + 1 + rightDown <= 7)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + rightDown)), chess_map_y - (world_chess_size * (i + 1 + rightDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //����
                        int leftDown;
                        for (leftDown = 0; leftDown < 8; leftDown++)
                        {
                            if (map[i + 1 + leftDown][j - 1 - leftDown] != 0 || i + 1 + leftDown > 7 || j - 1 - leftDown < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + leftDown][j - 1 - leftDown] >= 1 && map[i + 1 + leftDown][j - 1 - leftDown] <= 6 && i + 1 + leftDown <= 7 && j - 1 - leftDown >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - leftDown)), chess_map_y - (world_chess_size * (i + 1 + leftDown)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�O����
                        int fore;
                        for (fore = 0; fore < 8; fore++)
                        {
                            if (map[i - 1 - fore][j] != 0 || i - 1 - fore < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i - 1 - fore][j] >= 1 && map[i - 1 - fore][j] <= 6 && i - 1 - fore >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i - 1 - fore)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�����
                        int behi;
                        for (behi = 0; behi < 8; behi++)
                        {
                            if (map[i + 1 + behi][j] != 0 || i + 1 + behi >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i + 1 + behi][j] >= 1 && map[i + 1 + behi][j] <= 6 && i + 1 + behi >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * (i + 1 + behi)));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //������
                        int left;
                        for (left = 0; left < 8; left++)
                        {
                            if (map[i][j - 1 - left] != 0 || j - 1 - left < 0)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j - 1 - left] >= 1 && map[i][j - 1 - left] <= 6 && j - 1 - left >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j - 1 - left)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                        //�E����
                        int right;
                        for (right = 0; right < 8; right++)
                        {
                            if (map[i][j + 1 + right] != 0 || j + 1 + right >= 8)
                                break;
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }
                        if (map[i][j + 1 + right] >= 1 && map[i][j + 1 + right] <= 6 && j + 1 + right >= 0)
                        {
                            glPushMatrix();
                            glTranslatef(circle_x, chess_map_x - (world_chess_size * (j + 1 + right)), chess_map_y - (world_chess_size * i));
                            chess_masu.makeWithBlend(1, 0, 0, colorSita);
                            glPopMatrix();
                        }

                    }
                    else
                    {
                        glPushMatrix();
                        glTranslatef(circle_x, chess_map_x - (world_chess_size * j), chess_map_y - (world_chess_size * i));
                        chess_circle.make_Color(0, 0, 0.2);
                        chess_Q.make_Color(1, 1, 1);
                        glPopMatrix();
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void makeAnim(float r, float g, float b, obj o[], GLuint tex, int anim , int MaxFrame)
{

    int myframe = anim % MaxFrame;

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, o[myframe].vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, o[myframe].normalVBO);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, o[myframe].uvVBO);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0, o[myframe].vertex.size() / 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void roadAnimMesh(int ff,int ef,const char* path,const char* tex,obj o[])
{

    std::stringstream ss;
    ss << path << "_frame_" << std::to_string(currentAnimNum + ff) << ".txt"; 
    std::string filename = ss.str();
    o[currentAnimNum].Data = fopen(filename.c_str(),"r");
    //fopen_s(&o[currentAnimNum].Data, filename.c_str(), "r");
    if (o[currentAnimNum].Data == NULL)
    {
        printf("file error!! anim %d\n",currentAnimNum);
        return;
    }
    else
    {
        printf("success!! anim\n");
        char c;
        GLfloat x, y, z;
        while (fscanf(o[currentAnimNum].Data, "%c,%f,%f,%f", &c, &x, &y, &z) != EOF)
        {
            
            switch (c)
            {
            case 'v':
                o[currentAnimNum].vertex.push_back(x);
                o[currentAnimNum].vertex.push_back(y);
                o[currentAnimNum].vertex.push_back(z);
                o[currentAnimNum].vertexDataSize++;
                break;
            case 'u':
                o[currentAnimNum].UV.push_back(x);
                o[currentAnimNum].UV.push_back(y);
                o[currentAnimNum].UVDataSize++;
                break;
            case 'n':
                o[currentAnimNum].flat.push_back(x);
                o[currentAnimNum].flat.push_back(y);
                o[currentAnimNum].flat.push_back(z);
                o[currentAnimNum].flatDataSize++;
                break;
            default:
                break;
            }
        }
    }
    if (currentAnimNum == 0)
    {
        glGenTextures(1, &o[0].textureID);
        glBindTexture(GL_TEXTURE_2D, o[0].textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(tex, &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

            gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    o[currentAnimNum].setupVBO();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.11, 0, 0);
    loadinganim.make(1.0f,1.0f,1.0f);
    glPopMatrix();

    makeLoadingCount(currentAnimNum, ef - ff);

    currentAnimNum++;
    if (currentAnimNum > ef - ff)
    {
        printf("complete anim %s\n",path);
        currentMeshNum++;
        currentAnimNum = 0;
    }

}

void readAnim(int frame)
{
    switch (frame)
    {
    case 0:
        roadAnimMesh(1, 22, "config/anim/left", "config/image/left.png", left);
        break;
    case 1:
        roadAnimMesh(1, 25, "config/anim/back", "config/image/back.png", back);
        break;
    case 2:
        roadAnimMesh(1, 26, "config/anim/forward", "config/image/forward.png", forward);
        break;
    case 3:
        roadAnimMesh(1, 16, "config/anim/dash", "config/image/dash.png", dash);
        break;
    case 4:
        roadAnimMesh(1, 75, "config/anim/Idle", "config/image/idle.png", Idle);
        break;
    case 5:
        roadAnimMesh(1, 41, "config/anim/jump", "config/image/jump.png", jump);
        break;
    case 6:
        roadAnimMesh(1, 22, "config/anim/right", "config/image/right.png", right);
        break;
    default:
        currentMeshNum = 0;
        mainloopcount++;
        break;
    }
}

void preReadPoints()
{
    loadingmesh.load("config/mesh/loadingmesh.txt",true);
    loadinganim.load("config/mesh/loadinganim.txt",true);
    num_0.load("config/mesh/num_0.txt", true);
    num_1.load("config/mesh/num_1.txt", true);
    num_2.load("config/mesh/num_2.txt", true);
    num_3.load("config/mesh/num_3.txt", true);
    num_4.load("config/mesh/num_4.txt", true);
    num_5.load("config/mesh/num_5.txt", true);
    num_6.load("config/mesh/num_6.txt", true);
    num_7.load("config/mesh/num_7.txt", true);
    num_8.load("config/mesh/num_8.txt", true);
    num_9.load("config/mesh/num_9.txt", true);
    aincradIMAGE.load("config/mesh/aincradIMAGE.txt","config/image/aincradIMAGE.png");
	raceIMAGE.load("config/mesh/raceIMAGE.txt","config/image/raceIMAGE.png");
	shootingIMAGE.load("config/mesh/shootingIMAGE.txt","config/image/shootingIMAGE.png");
	tankIMAGE.load("config/mesh/tankIMAGE.txt","config/image/tankIMAGE.png");
	chessIMAGE.load("config/mesh/chessIMAGE.txt","config/image/chessIMAGE.png");
    parkIMAGE.load("config/mesh/parkIMAGE.txt","config/image/parkIMAGE.png");
}
