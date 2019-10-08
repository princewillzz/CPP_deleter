#include<iostream>
#include<dirent.h>
#include<string.h>
#include<vector>
#include<unistd.h>
using namespace std;

void delete_files(char*);
int delete_empty_folders(char*);

int main(int argc, char const *argv[]) {
  char dir_name[100];
  strcpy(dir_name, argv[--argc]);
  delete_files(dir_name);
  delete_empty_folders(dir_name);
  return 0;
}

int delete_empty_folders(char* dir_name) { int count = 0;
     string path = "rmdir ";
    
 // cout<<"in the directory "<<dir_name<<endl;

  DIR *dir;
  struct dirent *ent;
  
  dir = opendir(dir_name);


  if((ent = readdir(dir))) {
    path.append(string(dir_name));
    system(path.c_str());
    cout<<"deleted folder :"<<path;
  }
  while((ent = readdir(dir)) != NULL) { count ++;
    path.append(string(ent->d_name));
    if (!strstr(ent->d_name, ".")) {
      //cout<<endl<<"In the sub directory "<<ent->d_name<<" :";
      string top = string(dir_name) + "\\" + string(ent->d_name);
      char topic[100];
      strcpy(topic, top.c_str());
      delete_empty_folders(topic);}

    }

  
    return 0;
}



void delete_files(char* dir_name) {
  DIR *dir;
  struct dirent *ent;
  int i, count = 0;

  vector<string> keywoard;
  keywoard.push_back(".xml");
  keywoard.push_back(".html");
  keywoard.push_back(".htm");
  keywoard.push_back(".png");
  keywoard.push_back(".jpg");
  keywoard.push_back(".js");
  keywoard.push_back(".css");
  keywoard.push_back(".gif");
  keywoard.push_back(".psd");
  keywoard.push_back(".svg");
  keywoard.push_back(".eot");
  keywoard.push_back(".ttf");
  keywoard.push_back(".woff");
  keywoard.push_back(".srt");


  dir = opendir(dir_name);
  if(!dir) {
    cout<<"file opening error";
    return ;
  }
  cout<<"directory "<<dir_name<<endl;

 
  while((ent = readdir(dir)) != NULL) {

    string path = "del ";
    path.append(string(dir_name) + "\\" + string(ent->d_name));
    for(i = 0; i < keywoard.size(); i++) {
      if (strstr(path.c_str(), keywoard[i].c_str())) {
        system(path.c_str());
        //cout<<i<<" ";
        //cout<<path<<" ";
      
    } else if (!strstr(ent->d_name, ".")) {
      //cout<<endl<<endl<<"In the sub directory "<<ent->d_name<<" :";
      string top = string(dir_name) + "\\" + string(ent->d_name);
      char topic[100];
      strcpy(topic, top.c_str());
      delete_files(topic);}

    }
 
  }
  return;
}
