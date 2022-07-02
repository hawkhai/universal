/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CString.cpp
 * Author: bqh
 * 
 * Created on November 19, 2018, 4:05 PM
 */

#include "ZString.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

using namespace std;

CString::CString()
{
    m_pStr = NULL;
    m_len = 0;
}

CString::CString(const char *p)
{
    m_pStr = NULL;
    m_len = 0;
    if(p != NULL)
    {
        StrCpy(p);
    }
}

CString::CString(const CString &c)
{
    m_pStr = NULL;
    m_len = 0;
    if(this == &c)
    {
        return;
    }
    if(c.m_len != 0)
    {
        StrCpy(c.m_pStr);
    }
}

char *CString::Add(const char *pStr, int nBufSize) const
{
    char *pBuf = new char[nBufSize];
    char *pTemp = pBuf;

    for(int i = 0; i < m_len; i++)
    {
        pTemp[i] = m_pStr[i];
    }

    if(NULL != pStr)
    {
        int j = 0;        
        for(int i = m_len; j < nBufSize - m_len; j++, i++)
        {
            pTemp[i] = pStr[j];
        }
    }

    return pBuf;
}

CString::~CString()
{
    delete [] m_pStr;
}

char * CString::GetStr()
{
    return m_pStr;
}

int CString::GetLength()
{
    return m_len;
}

void CString::Release()     //��ʼ������
{
    if(NULL != m_pStr)
    {
        delete []m_pStr;
        m_pStr = NULL;
        m_len = 0;
    }
}

char* CString::Copy(const char *pStrSrc)   //�ַ�������
{
    char *pStr = m_pStr;
    for(; '\0' != (*pStr++ = *pStrSrc++); );

    return m_pStr;
    
}

//�ַ�������string
char* CString::StrCpy(const char *pStrSrc)
{
    if(NULL != pStrSrc)
    {
        Release();
        
        m_len = strlen(pStrSrc);
        m_pStr = new char[m_len + 1];
        
        Copy(pStrSrc);
    }
    return m_pStr;
}

//�ַ�������obj
char* CString::StrCpy(const CString &r)
{
    Release();
    
    if(0 != r.m_len)
    {
        m_len = r.m_len;
        m_pStr = new char[m_len + 1];
        
        Copy(r.m_pStr);
    }
    
    return m_pStr;
}

//��ֵ���������
CString& CString::operator = (const CString &r)  //����ΪCString����
{
    if(this != &r) //�����ǽ��Լ����Լ�
    {
        if(0 != r.m_len)
        {
            StrCpy(r); //ʹ���ַ����������غ���
            //StrCpy(r.m_pStr);
        }
    }
    
    return *this;
}

//��ֵ���������
CString& CString::operator = (const char *pStr)                             //����Ϊ�ַ����������д�����ϵͳ�Զ�����Ĭ���ַ����������ӣ�                                            
{                                                                           //obj = "test" ->(1)��ʱ���� = CString("test"); (2)obj = ��ʱ����
    if(NULL != pStr)                                                        //���д�������������ʡȥ���������ʱ������̣������Դ���ռ任ȡЧ��
    {
        StrCpy(pStr);
    }
    
    return *this;
}

bool CString::operator==(CString &m)
{
    char *sSoure = m.GetStr();
    if (strcmp(m_pStr, sSoure))
        return false;
    else
        return true;

}

CString CString::operator +(const CString &r) const //obj + obj
{
    CString obj;
    if(NULL != m_pStr && NULL != r.m_pStr)
    {
        char *pBuf = Add(r.m_pStr, m_len + r.m_len+1);
        obj = pBuf;
        delete []pBuf;
    }

    return obj;
}

CString CString::operator +(const char *pStr) const                         // obj + "String"
{
    CString obj;
    if(NULL != m_pStr && NULL != pStr)
    {
        int nSize = (NULL != pStr)?strlen(pStr):0;
        char *pBuf = Add(pStr, m_len+nSize+1);
        obj = pBuf;
        delete []pBuf;
    }
    return obj;
}


CString operator + (const char *pStr, const CString &r)                   //"String" + obj
{
    if(NULL != pStr && NULL != r.m_pStr)
    {
        CString temp = pStr;
        return temp+r;
    }

    return NULL;
}


CString CString::operator += (const CString &r)                     // obj += obj
{
    *this = *this + r;

    return *this;
}

CString CString::operator += (const char *pStr)                       // obj += "String"
{
    *this = *this + pStr;

    return *this;
}

char * CString::GetBuffer()
{    
    char *p;
    p = new char[m_len];
    for (int i = 0; i < m_len; i++)
        *(p + i) = *(m_pStr + i);

    return p;
}

CString CString::Left(int len)
{
    if (len > m_len)
        len = m_len;
    char *p;
    p = new char[len];
    for (int i = 0; i < len; i++)
        *(p + i) = *(m_pStr + i);
    CString strRet(p);
    return strRet;

}

CString CString::Right(int len)
{
    int j = 0;
    if (len > m_len)
        len = m_len;
    char *p;
    p = new char[len];
    for (int i = m_len - len; i < m_len; i++)
    {
        *(p + j) = *(m_pStr + i);
        j++;
    }
    CString strRet(p);
    return strRet;
}

void CString::Display()
{
    //cout << m_pStr << endl;
}

bool CString::Compare(CString &strDes)
{
    char *p = strDes.GetStr();
    if (!strcmp(m_pStr, p))
        return true;
    else
        return false;

}

bool CString::Compare(char *sDes) //�Ƚ��Ӵ��Ƿ����;
{
    if (!strcmp(m_pStr, sDes))
        return true;
    else
        return false;

}

int CString::Find(char *subStr, int start) //��start��ʼ,�����Ӵ�subStr�ĵ�һ��λ��.
{
        assert(start < m_len);
        int i = start;
        int j = 0, pos = 0, len = strlen(subStr);

        if (len > m_len)
            return -1;
        else
        {
            while (m_pStr[i] != '\0')
            {
                if (m_pStr[i] != subStr[j])
                {
                    i++;
                    j = 0; //����һ���ַ�����ʼ�Ƚ�

                }
                else //����ͬ���ַ���
                {
                    if (j == 0)
                        pos = i;
                    i++;
                    j++;
                    if (j == len)
                        return pos;
                    if (i == m_len)
                        return -1;
                }
            }
            return -1;
        }
}

int  CString::ReverseFind(char *str)
{
    int ret = -1;
    for(int i = m_len - 1; i > -1; i--)
    {
        if(m_pStr[i] == str[0])
        {
            ret = i;
            break;
        }
    }
    return ret;
}

CString CString::Replace(char *subOld, char *subNew, int start) //�����滻���µ��ַ���
{
    int i;
    int pos = Find(subOld, start);
    if (pos == -1)
        return *this; //����û���滻��,����ԭ���Ĵ�;
    else //�������Ӵ�,λ��Ϊpos;
    {
        char *p1, *p2;
        if (pos >= 1)
        {
            p1 = new char[pos + 1]; //����+1;
            for (i = 0; i < pos; i++)
                p1[i] = m_pStr[i];
            p1[i] = '\0';
        }
        else
            p1 = "";


        if ((pos + (int) strlen(subOld)) < m_len) //˵�����滹���ַ���
        {
            int j = 0;
            p2 = new char[m_len - pos - (int) strlen(subOld) + 1];
            for (i = pos + (int) strlen(subOld); i < m_len; i++)
            {
                *(p2 + j) = *(m_pStr + i);
                j++;
            }
            p2[j] = '\0';
        }
        else
            p2 = "";

        char *p3 = new char[(int) strlen(subNew) +(int) strlen(p2)];
        strcpy(p3, subNew);
        strcat(p3, p2);

        char *p4 = new char[(int) strlen(p3) +(int) strlen(p1)];
        strcpy(p4, p1);
        strcat(p4, p3);
        delete p1;
        delete p2;

        CString strRet(p4);
        return strRet;

    }

}

CString CString::Delete(int nIndex, int nCount)//ɾ����nIndex��ʼ��nCount���ַ�,�õ��µĵ��ַ���.
{

    assert((nIndex + nCount) <= m_len);
    char *p1, *p2;
    int i;
    if (nIndex >= 1) //����ɾ��ǰ�滹���ַ���
    {
        p1 = new char[nIndex + 1];
        for (i = 0; i < nIndex; i++)
            *(p1 + i) = *(m_pStr + i);
        p1[i] = '\0';
    }
    else
        p1 = "";
    if ((nIndex + nCount) < m_len) //�������滹���ַ���
    {
        p2 = new char[m_len - nIndex - nCount + 1];
        int j = 0;
        for (i = nIndex + nCount; i < m_len; i++)
        {
            *(p2 + j) = *(m_pStr + i);
            j++;
        }
        p2[j] = '\0';
    }
    else
        p2 = "";
    char *tem = new char[m_len - nCount];
    strcpy(tem, p1);
    strcat(tem, p2);
    delete p1;
    delete p2;

    CString strRet(tem);
    return strRet;
}

CString CString::Insert(int nIndex, char *pstr)
{
    assert(nIndex >= 0 && nIndex < m_len);
    char *p1, *p2, *p3;
    p1 = new char[nIndex + 1];
    int i = 0;
    for (i = 0; i < nIndex; i++)
        p1[i] = m_pStr[i];
    p1[i] = '\0';

    p2 = new char[m_len - nIndex + 1];
    int j = 0;
    for (i = nIndex; i < m_len; i++)
    {
        p2[j] = m_pStr[i];
        j++;
    }
    p2[j] = '\0';

    p3 = new char[(int) strlen(p2) + (int) strlen(pstr)];
    strcpy(p3, pstr);
    strcat(p3, p2);

    char *tem = new char[m_len + (int) strlen(pstr)];
    strcpy(tem, p1);
    strcat(tem, p3);
    delete p1;
    delete p2;

    CString strRet(tem);
    return strRet;


}

CString CString::Remove(char *pstr, int start)
{
    int pos = Find(pstr, start);
    if (pos == -1)
        return *this;
    else
    {
        int len = strlen(pstr);
        char *p1, *p2;
        if (pos >= 1)
        {
            p1 = new char[pos + 1];
            int i = 0;
            for (i = 0; i < pos; i++)
                p1[i] = m_pStr[i];
            p1[i] = '\0';
        }
        else
            p1 = "";
        if (pos + len < m_len)
        {
            p2 = new char[m_len - pos - len + 1];
            int j = 0;
            for (int i = pos + len; i < m_len; i++)
            {
                p2[j] = m_pStr[i];
                j++;
            }
            p2[j] = '\0';
        }
        char *tem = new char[m_len - len];
        strcpy(tem, p1);
        strcat(tem, p2);
        CString strRet(tem);
        return strRet;
    }

}

CString CString::Mid(int nFirst, int nEnd) //�õ���nFirst��nEnd���ַ���
{
    assert(nFirst >= 0 && nFirst <= nEnd && nEnd < m_len);
    char *p1;
    p1 = new char[nEnd - nFirst + 2];
    int j = 0;
    for (int i = nFirst; i < nEnd; i++)
    {
        p1[j] = m_pStr[i];
        j++;
    }
    p1[j] = '\0';

    CString strRet(p1);
    return strRet;

}
