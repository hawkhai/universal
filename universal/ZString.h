/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CString.h
 * Author: bqh
 *
 * Created on November 19, 2018, 4:05 PM
 */

#ifndef CSTRING_H
#define CSTRING_H

#include <string>
#include <assert.h>
using namespace std;

class CString {
     friend CString operator + (const char *pStr, const CString &r);
public:
 CString();          

 CString(const char *p);  

 CString(const CString &c); 

 ~CString();             
public:
	char *StrCpy(const char *pStrSrc);
        char *StrCpy(const CString &r);
        CString &operator=(const char *p);
        CString &operator=(const CString &m);
        CString operator +(const CString &r) const; //obj + obj
        CString operator +(const char *pStr) const; // obj + "String"
        CString operator += (const CString &r);  // obj += obj
        CString operator += (const char *pStr);  // obj += "String"  
        bool    operator==(CString &m);
        bool    operator>=(CString &m);
        void    Display();
        int     GetLength();
        char   *GetBuffer();
        CString Left(int len);
        CString Right(int len);
        bool    Compare(CString &strDes);
        bool    Compare(char *sDes);
        int     Find(char *strSub,int nstart=0); 
        int     ReverseFind(char *str);
        CString Replace(char *subOld,char *subNew,int start=0);
        CString Delete(int nIndwx,int nCount =1);
        CString Insert(int nIndex,char *pstr);
        CString Remove(char *pstr,int start=0);
        CString Mid(int nFirst,int nEnd);
        CString Trim(char *strDest,int nstart);
private:
        char*   m_pStr;
        int     m_len;
        char*   GetStr();
        char *Add(const char *pStr, int nBufSize) const;
	char *Copy(const char *pStrSrc);
	void Release();
};

#endif /* CSTRING_H */



