#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 100
//Name of presenters: Amit Shwartz ID 305432775 & Roni Polisanov ID 307835884

typedef struct _wagon
{
    char* id;
    char* priority;
    char* target;
    char* location;
    struct _wagon *next_wagon;
}wagon;

typedef struct _station
{
    char* name;
    wagon *waitlist;
    wagon *parklist;
    struct _station *next_station;
}station;

// מוסיפה את התחנות שהתקבלו מהקובץ לפי הסדר
station* add_station(char *line, station *head,FILE* output)
{
    static int num=1;
    if (strcmp(head->name,"start") == 0)
    {
        strcpy(head->name,line);
        fprintf(output, "%d. %s\n", num, head->name);
        ++num;
        return head;
    }
    station *newstation = (station*)malloc(1*sizeof(station));
    if (newstation == NULL)
    {
        printf("Error in allocating station, returning NULL\n");
        return NULL;
    }
    char *new_name= (char*)malloc(sizeof(line));
    if (newstation == NULL)
    {
        printf("Error in allocating new_name, returning NULL\n");
        return NULL;
    }
        strlcpy(new_name,line,10);
        newstation->name=new_name;
        newstation->waitlist=NULL;
        newstation->parklist=NULL;
        newstation->next_station = head;
        fprintf(output, "%d. %s",num,new_name);
        ++num;
        return newstation;
}

// מפזרת ויוצרת  את הקרונות למיקום הנוכחי שלהם
wagon* add_cart(char* line, wagon* head, station* STATION, FILE* output)
{
    char *temp_id,*temp_pri,*temp_loc,*temp_tar;
    station *temp=STATION;
    const char s[2]=" ,";
    char * token;
    temp_id=(char*)malloc(10*sizeof(char));
    if (temp_id == NULL)
    {
        printf("Error in allocating temp_id, returning NULL\n");
        return NULL;
    }
    temp_pri=(char*)malloc(10*sizeof(char));
    if ( temp_pri == NULL)
    {
        printf("Error in allocating temp_pri, returning NULL\n");
        return NULL;
    }
    temp_loc=(char*)malloc(10*sizeof(char));
    if ( temp_loc == NULL)
    {
        printf("Error in allocating temp_loc, returning NULL\n");
        return NULL;
    }
    temp_tar=(char*)malloc(10*sizeof(char));
    if (temp_tar == NULL)
    {
        printf("Error in allocating temp_tar, returning NULL\n");
        return NULL;
    }
    wagon *new_cart=(wagon*)malloc(sizeof(wagon));
    if (new_cart== NULL)
    {
        printf("Error in allocating cart, returning NULL\n");
        return NULL;
    }
    new_cart->next_wagon=NULL;

	token = strtok(line, s);
	strlcpy(temp_id,token,10);
    new_cart->id = temp_id;

    token = strtok(NULL, s);
	strlcpy(temp_pri,token,10);
    new_cart->priority = temp_pri;

    token = strtok(NULL, s);
	strlcpy(temp_loc,token,10);
    new_cart->location = temp_loc;

    token = strtok(NULL, s);
	strlcpy(temp_tar,token,10);
    new_cart->target = temp_tar;

	if(strcmp( "Train",new_cart->location) == 0)
    {
        new_cart->next_wagon = head;
        fprintf(output,"Carts that go on train: [%s][%s][%s][%s]\n" ,new_cart->id , new_cart->priority , new_cart->location , new_cart->target );
        return new_cart;
    }

	while(strstr(temp->name,new_cart->location)==NULL)
    {
        temp=temp->next_station;
    }
         new_cart->next_wagon = temp->waitlist;
         temp->waitlist = new_cart;
         fprintf(output,"Cart ID[%s] located in: %s \n", temp->waitlist->id, temp->waitlist->location);
	 return head;
}

// בודקת את סדר העדיפות של הקרונות אשר יושבים בקטר באופן רקורסיבי
wagon*  priority_check(wagon* head)
 {
     wagon* current=head;
     wagon* next=head->next_wagon;
     wagon* temp;
     wagon* temp2;
     int value=0;
     while(current->next_wagon!=NULL)
     {
     value=strcmp(current->priority,next->priority);
     if(value<0)
     {
      temp=next->next_wagon;
      current->next_wagon=temp;
      next->next_wagon=current;
      temp2=next;
      next=current;
      current=temp2;
     }
     else
     {
      current->next_wagon=priority_check(next);
      next=current->next_wagon;
      if(strcmp(current->priority,next->priority)>=0)
          return current;
     }
     }
      return current;
}

//מבצעת את העמסת קרון מרשימת המתנה , נשלחת מפונקציית נסיעת הקטר
 wagon* load_cart(wagon* head, wagon* load,FILE* output)
 {
     wagon* temp_load;
     while(load!=NULL)
     {
        temp_load=load;
        load=load->next_wagon;
        temp_load->next_wagon = head;
        head = temp_load;
        fprintf(output,"cart ID[%s] loaded to the Train \n",head->id);
     }
     if(head != NULL)
     {
        head = priority_check(head);
     }
     return head;
 }

//פונקציית הנסיעה של הקטר הקטר יוריד את הקרונות לפי סדר העדיפות
// שנקבע לתוך החניה של תחנת היעד ויבדוק אם ניתןלהעמיס קרון שמחכה ברשימת ההמתנה
   wagon* on_the_road(wagon* katar,station* rail,FILE* output)
 {
    fprintf(output,"Next stop: %s \n", katar->target);
    station* temp_rail=rail;
    wagon* temp_katar=katar;

    while(strstr(temp_katar->target, temp_rail->name) == NULL)
    {
        temp_rail = temp_rail->next_station;
    }
    katar=katar->next_wagon;
    temp_katar->next_wagon = temp_rail->parklist;
    temp_rail->parklist = temp_katar;
    if(temp_rail->waitlist != NULL)
    {
        katar = load_cart(katar, temp_rail->waitlist,output);
        temp_rail->waitlist = NULL;
    }
        return katar;
 }

 //בודקת אם הרכבת ריקה אם כן אז היא עוברת בתחנות לפי הסדר ומעמיסה מרשימת ההמתנה אם יש קרונות
wagon* check_empty_train(wagon* head,station* rail,FILE* output)
 {
    station* temp_rail = rail;
    while(temp_rail->waitlist == NULL)
    {
        temp_rail=temp_rail->next_station;
        if(temp_rail==NULL)
            return head;
    }
    fprintf(output,"Train is empty>> loading to train from station: %s\n",temp_rail->name);
    while(temp_rail->waitlist != NULL)
    {
        temp_rail->waitlist->next_wagon = head;
        head = temp_rail->waitlist;
        fprintf(output,"cart ID[%s] \n",head->id);
        temp_rail->waitlist = temp_rail->waitlist->next_wagon;
    }
    head = priority_check(head);
        return head;
 }

   //סורקת את כל התחנות ברשימת הקרונות שחונים ומשחררת את הקצאות הזיכרון
void* free_all(station* rail)
{
    station* temp_rail;
    wagon* temp_cart;
    while(rail!=NULL)
    {
        temp_rail=rail;
        rail =rail->next_station;
            while(temp_rail->parklist!=NULL)
            {
                temp_cart=temp_rail->parklist;
                temp_rail->parklist=temp_rail->parklist->next_wagon;
                free(temp_cart->id);
                free(temp_cart->location);
                free(temp_cart->priority);
                free(temp_cart->target);
                free(temp_cart);
            }
        free(temp_rail);
    }
}

 int main(int argc, char * argv[])
{
    int x=0,y=0;
    char str[]="start";
    char line[LINE_SIZE] = { 0 };
    //יוצר את את הקטר
    wagon *katar=(wagon*)malloc(10*sizeof(wagon));
    if (katar== NULL)
    {
        printf("Error in allocating cart, returning NULL\n");
        return -1;
    }
    katar->next_wagon = NULL;
    // יוצר את התחנות
    station *rail=(station*)malloc(50*sizeof(station));
    if (rail== NULL)
    {
        printf("Error in allocating station, returning NULL\n");
        return -1;
    }
    rail->next_station=NULL;
    rail->waitlist=NULL;
    rail->parklist=NULL;
    rail->name=str;
    FILE *output= fopen("argv[2]","w");
    if (output == NULL)
    {
        printf("The file could not be opened\n");
        return (-1);
    }
    FILE *input = fopen("argv[1]","r");
    if (input == NULL)
    {
        printf("The file could not be opened\n");
        return (-1);
    }
    fprintf(output, "Loading stations:\n \n");
    while(fgets(line,100,input)!=NULL)
    {
        if(line[0]=='-')
            break;
        if(line[0]=='#')
            continue;
        rail = add_station(line,rail,output);
        while(y==0)
        {
            rail->next_station=NULL;
            ++y;
        }
        printf("%s",rail->name);
    }

    while(fgets(line,100,input)!=NULL)
    {
        if(line[0]=='#')
        {
            continue;
        }
        katar = add_cart(line, katar, rail, output);
        while(x==0)
        {
            katar->next_wagon=NULL;
            ++x;
        }
    }

    //בודק אם לא הועמס קרון לקטר
    if(katar==NULL)
    {
        katar = check_empty_train(katar,rail,output);
    }

    // מסדר את הקטר לפי עדיפות פעם ראשונה
    katar=priority_check(katar);
    fprintf(output,"Next stop: %s", katar->target);

    //כל עוד הקטר לא ריק הרכבת תסע לפי הסדר שנקבע לה אחרת תבדוק אם היא צריכה להעמיס קרונות
    while(katar!=NULL)
    {
        katar=on_the_road(katar,rail,output);
        if(katar==NULL)
        katar = check_empty_train(katar,rail,output);
    }
    printf("All carts reach destination.\n");
    fprintf(output, "\nAll carts reach destination.\nGood bye....");
    free_all(rail);
    fclose(output);
    fclose(input);
    return 1;
 }
