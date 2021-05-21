/*
    Coded By MKZ
*/

#include <stdio.h>
#include <stdlib.h>

int sizeOfString(char arr[]) // char dizilerinin \0 a kadar kısmının boyutu bulundu
{
    int i;
    for (i = 0; i < arr[i] != '\0'; i++)
    {
    }; // BOYUTBUL
    return i;
}

int registerDetector(char arr[]) // char dizisi aracılığı ile hangi tür olduğu belirlendi.
{
    if (arr[0] == 'A')
    {
        return 0;
    }
    else if (arr[0] == 'B')
    {
        return 1;
    }
    else if (arr[0] == 'C')
    {
        return 2;
    }
    else if (arr[0] == 'D')
    {
        return 3;
    }
    else if (arr[0] == '[') // RAM Konumu
    {
        return 4;
    }
    else // Literal
    {
        return 5;
    }
}

int charsToIntForLiteral(char arr[]) // char dizisi int e çevrilerek sabit hesaplandı.
{
    int i = 0, size = sizeOfString(arr);
    int result = 0;
    int negative = 0;

    if (arr[0] == '-')
    {
        negative = 1;
        i++;
    }

    for (i; i < size; i++)
    {
        int temp = (int)arr[i] - 48;
        result = result * 10;
        result += temp;
    }

    return negative == 1 ? result * -1 : result;
}

int charsToIntForRamAddress(char arr[]) // char dizisi int e çevrilerek ram adresi hesaplandı.
{
    int i, size = sizeOfString(arr);
    int result = 0;

    for (i = 1; i < size - 1; i++)
    {
        int temp = (int)arr[i] - 48;
        result = result * 10;
        result += temp;
    }

    return result;
}

int stringControl(char string1[], char string2[]) // verilen iki char arrayi kontrol edilir aynı ise 1 değilse 0 döner
{
    int size = sizeOfString(string1);
    int i;

    if (size == sizeOfString(string2))
    {
        for (i = 0; i < size; i++)
        {
            if (string1[i] != string2[i])
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

int statusRegisterContoller(short x) // status register kontolcüsü
{
    if (x == 0) // 0 eşitse 0
    {
        return 0;
    }
    else if (x > 0) // 0 dan büyükse 1
    {
        return 1;
    }
    else // değilse -1
    {
        return -1;
    }
}

int branchContoller(char arr[]) // Bir sonraki komut dallanma komutumu kontrol edilir.
{
    if (arr[0] == 'S' && arr[1] == 'S' && arr[2] == 'D' && arr[3] == '\0')
    {
        return 1;
    }
    else if (arr[0] == 'S' && arr[1] == 'S' && arr[2] == '\0')
    {
        return 1;
    }
    else if (arr[0] == 'S' && arr[1] == 'N' && arr[2] == '\0')
    {
        return 1;
    }
    else if (arr[0] == 'S' && arr[1] == 'P' && arr[2] == '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void intToBinaryConverter(int x) // verilen sayıyı binary tabanda yazdırmak
{
    char binary[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    int digit;

    if (x < 0) // negatif değerler için baş kısmına - koyduk
    {
        x = x * -1;
        printf("- ");
    }

    while (x > 0)
    {
        digit = x % 2;
        x = x / 2;
        binary[7 - i] = digit;
        i++;
    }

    for (i = 0; i < 8; i++)
    {
        printf("%d ", binary[i]);
    }
}

void printRawLetterData(int size, char arr[]) // Harf halinin yazdırılması
{
    int i;
    printf("Harf Hali : \n");
    for (i = 0; i < size; i++) // Harf halinin yazdırılması
    {
        if (arr[i] == ' ' || arr[i] == '\n' || arr[i] == '\t') // istenmeyen çıkışlar
        {
            continue;
        }
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void printTokenizedMatrix(int R, int C, char M[R][C]) // Kelimeleştirilmiş halin yazdırılması
{
    int i, j;
    printf("\nKelimelestirilmis Matris Hali : \n");
    for (i = 0; i < R; i++) // matrix halinin yazdırılması
    {
        for (j = 0; M[i][j] != '\0'; j++)
        {
            printf("%c", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    FILE *file;
    char *rawData; // ilk okumadaki karakterler için dizi
    char c, fileName[250];
    int totalCharSize = 0, i, j;
    rawData = (char *)calloc(totalCharSize, sizeof(char *)); // ilk boyutlandırma

    printf("Lutfen dosya ismini giriniz (or: file.txt) : ");
    gets(fileName);

    file = fopen(fileName, "r"); // dosyayı aç

    if (file == NULL) // Dosya varlık kontrolü
    {
        printf("Dosya okuma basarisiz.");
        return 0;
    }

    // DOSYA OKUMA ALANI

    while ((c = fgetc(file)) != EOF) // dosyadan karakter karakter okuma
    {
        rawData[totalCharSize] = c;                                         // okunan karakteri genişleyebilen dizeye atmak
        totalCharSize++;                                                    // boyutu 1 arttirmak
        rawData = (char *)realloc(rawData, totalCharSize * sizeof(char *)); // yeniden boyutlandırma
    }
    fclose(file); // dosyayı kapat

    // TOKENIZE EDILME ALANI

    int rowSize = 0;
    int columnSize = 0;
    int letterCounter = 0;
    for (i = 0; i < totalCharSize; i++) // ham data kullanılarak satır ve sütün sayısı hesaplandi.
    {
        if (rawData[i] != ' ' && rawData[i] != ',' && rawData[i] != ':' && rawData[i] != '\n') // bu karakterler geldiğinde alt satıra inildi.
        {
            letterCounter++;
        }
        else
        {
            if (letterCounter > columnSize) // en uzun kelime baz alınarak sutun sayısı elde edildi.
            {
                columnSize = letterCounter;
            }
            rowSize++;
            letterCounter = 0;
        }
    }
    rowSize++;    // son satırın hesaplanması için.
    columnSize++; // one more for '\0'

    char tokenizedData[rowSize][columnSize]; //Kelimelerin tutulması için matrix
    int R = 0, C = 0;

    int *labels;                            // etiketleme işlemi yapmak için
    int labelSize = 0;                      // etiket sayısı
    labels = (int *)calloc(1, sizeof(int)); // etiket adreslerini tutmak için başlattık

    for (i = 0; i < totalCharSize; i++) // Matrix'in doldurulması ve Etiket adreslerinin alınması
    {
        if (rawData[i] != ' ' && rawData[i] != ',' && rawData[i] != ':' && rawData[i] != '\n')
        {
            tokenizedData[R][C] = rawData[i];
            C++;
        }
        else
        {
            if (rawData[i] == ':') // etiketlerin diziye aktarılması
            {
                labels[labelSize] = R; // etiketin matris satır numarası
                labelSize++;
                labels = (int *)realloc(labels, labelSize * sizeof(int *)); // dizinin yeniden boyutlandırılması
            }
            tokenizedData[R][C] = '\0'; // insurance - finishing letter
            R++;
            C = 0;
        }
    }
    tokenizedData[R][C] = '\0'; // insurance - finishing letter

    // KODU ÇALIŞTIRMA ALANI

    short RAM[256];
    short ABCDX[4] = {0, 0, 0, 0}; // 0 = AX, 1 = BX, 2 = CX, 3 = DX Registerleri array şeklinde tutuluyor.
    short statusRegister;          // -1 = negatif , 0 = nötr , 1 = pozitif
    short programRegister;         // Bir sonraki komut dallanma komutu ise 1 değilse 0 dır.

    for (i = 0; i < rowSize; i++) // kodun işleme alınması
    {
        if (tokenizedData[i][0] == 'H' && tokenizedData[i][1] == 'R' && tokenizedData[i][2] == 'K' && tokenizedData[i][3] == '\0') // HRK
        {
            int reg1 = registerDetector(tokenizedData[i + 1]); // hangi register olduğu bulundu
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (reg1 != 4) // ilk operand [XXX] değilse
            {
                if (!(reg2 > 3)) // 2.operand AX,BX,CX,DX den biri değilse
                {
                    ABCDX[reg1] = ABCDX[reg2];
                }
                else
                {
                    if (reg2 == 4)
                    {
                        int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                        ABCDX[reg1] = RAM[ramAddress];
                    }
                    else
                    {
                        int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                        ABCDX[reg1] = literal;
                    }
                }
            }
            else
            {
                int ramAddress1 = charsToIntForRamAddress(tokenizedData[i + 1]);
                if (!(reg2 > 3))
                {
                    RAM[ramAddress1] = ABCDX[reg2];
                }
                else
                {
                    if (reg2 == 4)
                    {
                        int ramAddress2 = charsToIntForRamAddress(tokenizedData[i + 2]);
                        RAM[ramAddress1] = RAM[ramAddress2];
                    }
                    else
                    {
                        int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                        RAM[ramAddress1] = literal;
                    }
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]); // bir sonraki komut dallanma komutu mu kontrol edildi.

            if (programRegister == 1) // dallanma komutu ise status registerine değer ataması yapılır.
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }

            i += 2;
        }
        else if (tokenizedData[i][0] == 'T' && tokenizedData[i][1] == 'O' && tokenizedData[i][2] == 'P' && tokenizedData[i][3] == '\0') // TOP
        {
            int reg1 = registerDetector(tokenizedData[i + 1]);
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (!(reg2 > 3))
            {
                ABCDX[reg1] = ABCDX[reg1] + ABCDX[reg2];
            }
            else
            {
                if (reg2 == 4)
                {
                    int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] + RAM[ramAddress];
                }
                else
                {
                    int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] + literal;
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }
            i += 2;
        }
        else if (tokenizedData[i][0] == 'C' && tokenizedData[i][1] == 'I' && tokenizedData[i][2] == 'K' && tokenizedData[i][3] == '\0') // CIK
        {
            int reg1 = registerDetector(tokenizedData[i + 1]);
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (!(reg2 > 3))
            {
                ABCDX[reg1] = ABCDX[reg1] - ABCDX[reg2];
            }
            else
            {
                if (reg2 == 4)
                {
                    int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] - RAM[ramAddress];
                }
                else
                {
                    int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] - literal;
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }
            i += 2;
        }
        else if (tokenizedData[i][0] == 'C' && tokenizedData[i][1] == 'R' && tokenizedData[i][2] == 'P' && tokenizedData[i][3] == '\0') // CRP
        {
            int reg1 = registerDetector(tokenizedData[i + 1]);
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (!(reg2 > 3))
            {
                ABCDX[reg1] = ABCDX[reg1] * ABCDX[reg2];
            }
            else
            {
                if (reg2 == 4)
                {
                    int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] * RAM[ramAddress];
                }
                else
                {
                    int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] * literal;
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }
            i += 2;
        }
        else if (tokenizedData[i][0] == 'B' && tokenizedData[i][1] == 'O' && tokenizedData[i][2] == 'L' && tokenizedData[i][3] == '\0') // BOL
        {
            int reg1 = registerDetector(tokenizedData[i + 1]);
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (!(reg2 > 3))
            {
                ABCDX[3] = ABCDX[reg1] % ABCDX[reg2]; // Kalan DX Registerinde tutuluyor.
                ABCDX[reg1] = ABCDX[reg1] / ABCDX[reg2];
            }
            else
            {
                if (reg2 == 4)
                {
                    int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                    ABCDX[3] = ABCDX[reg1] % RAM[ramAddress];
                    ABCDX[reg1] = ABCDX[reg1] / RAM[ramAddress];
                }
                else
                {
                    int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                    ABCDX[3] = ABCDX[reg1] % literal;
                    ABCDX[reg1] = ABCDX[reg1] / literal;
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }
            i += 2;
        }
        else if (tokenizedData[i][0] == 'V' && tokenizedData[i][1] == 'E' && tokenizedData[i][2] == 'Y' && tokenizedData[i][3] == 'A' && tokenizedData[i][4] == '\0') // VEYA
        {
            int reg1 = registerDetector(tokenizedData[i + 1]);
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (!(reg2 > 3))
            {
                ABCDX[reg1] = ABCDX[reg1] | ABCDX[reg2];
            }
            else
            {
                if (reg2 == 4)
                {
                    int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] | RAM[ramAddress];
                }
                else
                {
                    int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] | literal;
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }
            i += 2;
        }
        else if (tokenizedData[i][0] == 'V' && tokenizedData[i][1] == 'E' && tokenizedData[i][2] == '\0') // VE
        {
            int reg1 = registerDetector(tokenizedData[i + 1]);
            int reg2 = registerDetector(tokenizedData[i + 2]);

            if (!(reg2 > 3))
            {
                ABCDX[reg1] = ABCDX[reg1] & ABCDX[reg2];
            }
            else
            {
                if (reg2 == 4)
                {
                    int ramAddress = charsToIntForRamAddress(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] & RAM[ramAddress];
                }
                else
                {
                    int literal = charsToIntForLiteral(tokenizedData[i + 2]);
                    ABCDX[reg1] = ABCDX[reg1] & literal;
                }
            }

            programRegister = branchContoller(tokenizedData[i + 3]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg1]);
            }
            i += 2;
        }
        else if (tokenizedData[i][0] == 'D' && tokenizedData[i][1] == 'E' && tokenizedData[i][2] == 'G' && tokenizedData[i][3] == '\0') // DEG
        {
            int reg = registerDetector(tokenizedData[i + 1]);

            if (!(reg > 3))
            {
                if (ABCDX[reg] >= 0)
                {
                    ABCDX[reg] = 255 - ABCDX[reg]; // işlemci 8 bit çalıştığı için 11111111 = 255; 11110000 + 00001111 = 255
                }
                else
                {
                    ABCDX[reg] = -255 - ABCDX[reg];
                }
            }
            else
            {
                int ramAddress = charsToIntForRamAddress(tokenizedData[i + 1]);
                if (RAM[ramAddress] >= 0)
                {
                    RAM[ramAddress] = 255 - RAM[ramAddress];
                }
                else
                {
                    RAM[ramAddress] = -255 - RAM[ramAddress];
                }
            }

            programRegister = branchContoller(tokenizedData[i + 2]);

            if (programRegister == 1)
            {
                statusRegister = statusRegisterContoller(ABCDX[reg]);
            }
            i++;
        }
        else if (tokenizedData[i][0] == 'S' && tokenizedData[i][1] == 'S' && tokenizedData[i][2] == 'D' && tokenizedData[i][3] == '\0') // SSD
        {
            if (statusRegister != 0 && programRegister == 1)
            {
                for (j = 0; j < labelSize; j++)
                {
                    int result = stringControl(tokenizedData[i + 1], tokenizedData[labels[j]]); // SSD den sonraki komut ile etiketler arasında eşleşme var mi?

                    if (result == 1) // var ise
                    {
                        i = labels[j] - 1; // ana çalışma döngüsünü geri veya ileri al.
                        break;
                    }
                }
            }
            programRegister = 0;
            i++;
        }
        else if (tokenizedData[i][0] == 'S' && tokenizedData[i][1] == 'S' && tokenizedData[i][2] == '\0') // SS
        {
            if (statusRegister == 0 && programRegister == 1)
            {
                for (j = 0; j < labelSize; j++)
                {
                    int result = stringControl(tokenizedData[i + 1], tokenizedData[labels[j]]);

                    if (result == 1)
                    {
                        i = labels[j] - 1;
                        break;
                    }
                }
            }
            programRegister = 0;
            i++;
        }
        else if (tokenizedData[i][0] == 'S' && tokenizedData[i][1] == 'N' && tokenizedData[i][2] == '\0') // SN
        {
            if (statusRegister == -1 && programRegister == 1)
            {
                for (j = 0; j < labelSize; j++)
                {
                    int result = stringControl(tokenizedData[i + 1], tokenizedData[labels[j]]);

                    if (result == 1)
                    {
                        i = labels[j] - 1;
                        break;
                    }
                }
            }
            programRegister = 0;
            i++;
        }
        else if (tokenizedData[i][0] == 'S' && tokenizedData[i][1] == 'P' && tokenizedData[i][2] == '\0') // SP
        {
            if (statusRegister == 1 && programRegister == 1)
            {
                for (j = 0; j < labelSize; j++)
                {
                    int result = stringControl(tokenizedData[i + 1], tokenizedData[labels[j]]);

                    if (result == 1)
                    {
                        i = labels[j] - 1;
                        break;
                    }
                }
            }
            programRegister = 0;
            i++;
        }
    }

    // CIKTI ALANI

    // printRawLetterData(totalCharSize,rawData); // Harf halinin yazdırılması
    // printTokenizedMatrix(rowSize,columnSize,tokenizedData); // Tokenize halin yazdırılması

    printf("\nAX :");
    printf("\n   Decimal: %d", ABCDX[0]);
    printf("\n   Binary: ");
    intToBinaryConverter(ABCDX[0]);
    printf("\nBX :");
    printf("\n   Decimal: %d", ABCDX[1]);
    printf("\n   Binary: ");
    intToBinaryConverter(ABCDX[1]);
    printf("\nCX :");
    printf("\n   Decimal: %d", ABCDX[2]);
    printf("\n   Binary: ");
    intToBinaryConverter(ABCDX[2]);
    printf("\nDX :");
    printf("\n   Decimal: %d", ABCDX[3]);
    printf("\n   Binary: ");
    intToBinaryConverter(ABCDX[3]);
    printf("\nDX register degeri son yapilan bolme isleminin kalanidir(Bolme yapilmadi ise 0'dir).\n");
}
