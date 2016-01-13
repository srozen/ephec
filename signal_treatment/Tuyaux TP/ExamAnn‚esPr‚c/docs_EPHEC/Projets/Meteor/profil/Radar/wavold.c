
int lecture_format(FILE * fileread,FormatChunk * format){
    int read_bytes;
    int formatSize = sizeof(FormatChunk);
    long Before;

    Before = ftell(fileread);
    read_bytes = fread(format,formatSize,1,fileread);
    fseek (fileread, Before + format->chunkSize + 8, SEEK_SET);

    return read_bytes;
}

void affichage_format(FormatChunk * format){
    printf("\nFormat Chunk:\n\nID : %s\nTaille de la partie : %d bytes\nCompression : %d\nCanaux : %hu\nFrequence d echantillonage : %u Hz\nNombre de bytes par seconde : %u bytes\nTaille d un echantillon : %u bytes\nQuantification : %u bits\n",format->chunkID,format->chunkSize,format->wFormatTag,format->wChannels,format->dwSamplesPerSec,format->dwAvgBytesPerSec,format->wBlockAlign,format->wBitsPerSample);
}

int lecture_datachunk(FILE * fileread,DataChunk * data,int size){
    int read_bytes,i;
    int dataSize = sizeof(DataChunk);
    long Before;

    Before = ftell(fileread);
    read_bytes = fread(data,dataSize,1,fileread);
    fseek (fileread, Before + data->chunkSize + 8, SEEK_SET);

    unsigned short int waveData[size];

    int r;
    int read_audio = 0;

    for(i=0;i<size;i+=2){
        Before = ftell(fileread);
        if((r = fread(&waveData[i],sizeof(unsigned short int),1,fileread)) == 2){
          read_bytes += 2;
          read_audio += 2;
        }
        fseek (fileread, Before + 2, SEEK_SET);
        printf("%hu ",waveData[i]);
    }

    printf("\n\nLu %d bytes",read_audio);

    return read_bytes;
}

void affichage_datachunk(DataChunk * data){
    printf("\n\nData Chunk:\n\nData id : %s\nData Length : %d",data->chunkID,data->chunkSize);
}

int lecture_wave_struct(char * wavefilepath){
   FILE * wavefile;

   FormatChunk format;
   DataChunk data;

   if(!(wavefile = fopen(wavefilepath,"rb"))){
      printf("Erreur le fichier %s n a pas pu etre ouvert!\n",wavefilepath);
      getchar();
      return 0;
   }
   else{
      printf("Le fichier %s a pu etre ouvert",wavefilepath);
      getchar();

      lecture_format(wavefile,&format);
      affichage_format(&format);


      getchar();

      lecture_datachunk(wavefile,&data,(10*format.dwSamplesPerSec*format.wBlockAlign));
      affichage_datachunk(&data);
      return 1;
   }
   fclose(wavefile);
}

