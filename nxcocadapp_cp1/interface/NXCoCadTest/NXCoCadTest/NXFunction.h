void createRect(double leftUpX,double leftUpY,double rightDownX,double rightDownY,double z);
void createRect(double leftUpY,double leftUpZ,double rightDownY,double rightDownZ,double x,int id,int id2);
void createRect(double leftUpX,double leftUpZ,double rightDownX,double rightDownZ,double y,int id);
void createSketch();
//void lashen(int height,int lineNum,int sketchNum,int sketchId);
void createPlane(int x);
void drawCircle(double x,double y,double z,double r);
//void createSketchOnExtrude(int extrudeNum,const char *str1,const char *str2);
//void fanxianglashen(const char *sketchId,const char *sketchNum,const char *lashenLine,const char *targetExtrue,int length);
void unDo();



char* getJournalId(char name[]);
char* getFeatureName(char name[]);
void lashen(int height,char targetSketchName[],char setName[]);
void fanxianglashen(char targetSketchName[],char targetExtrueName[],int length,char setName[]);
void createSketchOnExtrude(char targetExtrude[],char *str1,char *str2,char setName[]);
void qiuhe(char *targetExtrueName1,char *targetExtrueName2,char *setName);
void daojiao(char *targetSketchName,char *str2,char *r,char *setName);