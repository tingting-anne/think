#include "HashMap.h"
#include <string>
#include <iostream>



class HashFunc
{
public:
    static int hashCode(const std::string & key)
    {
        int hash = 0;
        for(size_t i = 0; i < key.length(); ++i)
        {
            hash = hash << 7 ^ key[i];
        }
        return (hash & 0x7FFFFFFF);
    }
};

//Equal function you provided to check whether two Keys are equal
//must be correspond to the type of the Key
class EqualKey
{
public:
    static bool equals(const std::string & A ,const std::string & B)
    {
        if(A.compare(B) == 0)
            return true;    //if equal return true
        else
            return false;    //else false
    }
};

int test_hashmap()
{
    HashMap<std::string,std::string,HashFunc,EqualKey> hm;

    hm.insert("hello" , "you");
    hm.insert("why" , "dream");
    hm.insert("java" ,"good");
    hm.insert("welcome" ,"haha");

    hm.insert("welcome" ,"hehe"); //error, key-value must be unique


    std::cout<<"after insert:"<<std::endl;
    std::cout<<hm.find("welcome")<<std::endl;
    std::cout<<hm.find("java")<<std::endl;
    std::cout<<hm["why"]<<std::endl;
    std::cout<<hm["hello"]<<std::endl;

    if(hm.remove("hello"))
        std::cout<<"remove is ok"<<std::endl;    //remove is ok
    std::cout<<hm.find("hello")<<std::endl; //not exist print NULL

    hm["why"] = "love"; //modify the value 
    std::cout<<hm["why"]<<std::endl;

    return 0;
}
