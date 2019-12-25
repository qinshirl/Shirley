int base64(char *s,char *d)
{
	char CharSet[64]={
		'A','B','C','D','E','F','G','H',
			'I','J','K','L','M','N','O','P',
			'Q','R','S','T','U','V','W','X',
			'Y','Z','a','b','c','d','e','f',
			'g','h','i','j','k','l','m','n',
			'o','p','q','r','s','t','u','v',
			'w','x','y','z','0','1','2','3',
			'4','5','6','7','8','9','+','/'};
		unsigned char In[3];
		unsigned char Out[4];
		int cnt=0;
		if(!s||!d) return 0;
		//for(;*s!=0;)
		for (int n = 1; n <= 16; /*++n*/)
		{
			if(cnt+4>76)
			{
				*d++='\n';
				cnt=0;
			}
			//if(strlen(s)>=3)
			if(n <= 14)
			{
				In[0]=*s;
				In[1]=*(s+1);
				In[2]=*(s+2);
				Out[0]=In[0]>>2;
				Out[1]=(In[0]&0x03)<<4|(In[1]&0xf0)>>4;
				Out[2]=(In[1]&0x0f)<<2|(In[2]&0xc0)>>6;
				Out[3]=In[2]&0x3f;
				*d=CharSet[Out[0]];
				*(d+1)=CharSet[Out[1]];
				*(d+2)=CharSet[Out[2]];
				*(d+3)=CharSet[Out[3]];
				s+=3;
				d+=4;
				n+=3;
			}
			//else if(strlen(s)==1)
			else if (n == 16)
			{
				In[0]=*s;
				Out[0]=In[0]>>2;
				Out[1]=(In[0]&0x03)<<4|0;
				*d=CharSet[Out[0]];
				*(d+1)=CharSet[Out[1]];
				*(d+2)='=';
				*(d+3)='=';
				s+=1;
				n+=1;
				d+=4;
			}
			//else if(strlen(s)==2)
			else if (n == 15)
			{
				In[0]=*s;
				In[1]=*(s+1);
				Out[0]=In[0]>>2;
				Out[1]=(In[0]&0x03)<<4|(In[1]&0xf0)>>4;
				Out[2]=(In[1]&0x0f)<<2|0;
				*d=CharSet[Out[0]];
				*(d+1)=CharSet[Out[1]];
				*(d+2)=CharSet[Out[2]];
				*(d+3)='=';
				s+=2;
				n+=2;
				d+=4;
			}
			cnt+=4;
		}
		*d='\0';
		return 1;
}