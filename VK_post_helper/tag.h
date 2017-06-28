#ifndef TAG_H
#define TAG_H

#include <element_bd.h>

class fabrika_tg_gr_ac;

class tag : public element_bd
{

public:

    QString GetNameTag();
    bool operator==(tag *right)
    {
        return this->GetNameTag() == right->GetNameTag();
    }
    bool operator==(tag right)
    {
        bool b = this->GetNameTag() == right.GetNameTag();
        return b;//this->GetNameTag() == right.GetNameTag();
    }

    int getCountPost(){return count_post;}
    int getCountItem(){return count_item;}
    void setCountItem(int count){this->count_item=count<0?0:count;}
    void setCountPost(int count){this->count_post=count<0?0:count;}
    int upCountPost(){return (count_post++);}
    int upCountItem(){return (count_item++);}
    int downCountItem(){
        count_item = count_item<=0?0:count_item-1;
        return count_item;
    }
    int downCountPost(){
        count_post = count_post<=0?0:count_post-1;
        return count_post;
    }



    friend fabrika_tg_gr_ac;
private:
    explicit tag(QString name,int id_BD, QString name_table);
    void setTagName(QString tagname){this->tag_name = tagname;}


QString tag_name;
int count_item;
int count_post;




// element_bd interface
public:
QString getName();
};


#endif // TAG_H
