#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "incode.h"
#include "comm.h"
/*vaϵ�к�ļ�����.System V Unix��va_start����Ϊֻ��һ�������ĺ�: 
����va_start(va_list arg_ptr);
    ��ANSI C����Ϊ: 
����va_start(va_list arg_ptr, prev_param);
�����������Ҫ��system V�Ķ���,Ӧ����vararg.hͷ�ļ���������ĺ�,
	  ANSI C�ĺ��system V�ĺ��ǲ����ݵ�,����һ�㶼��ANSI C,������ANSI C�Ķ���͹���,Ҳ���ڳ������ֲ. */
static si_t use_function(struct egui_uds* uds_ptr,function_type fun_type,...)
{
	int ret=0;
	char buffer[1024];
	va_list arg_ptr;
	int ptr_num[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	si_t par_buf[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};     //�󲿷ֵĲ������Ͷ�Ϊsi_t,��಻����10��
	int par_buf_i=0;     //�����par_buf�ļ�����
	char* title=NULL;     //һ��char*ΪӦ�ó���ı���
	int i=0;
	va_start(arg_ptr,fun_type);
	while(i<10)
	{
		int type;
		if(-1 == (type=get_parameter_type(fun_type,i)))
		{
			break;
		}
		else if(1==type)
		{
			par_buf[par_buf_i]=va_arg(arg_ptr,si_t);  
			par_buf_i++;
		}
		else if(2==type)                   //!!!!�����֮���ٲ���������͵Ĳ���
		{
			title=va_arg(arg_ptr,char*);
		}
		i++;
	}
	va_end(arg_ptr);
	char* tmp=buffer;
	int length=0   ; //������ĳ���
	int par_type=-1;      
	//װ��ͷ�����Ȱѳ�������Ϊ�㣬�Ȳ��������ɺ����޸ĳ���ֵ
	*tmp=fun_type;
	tmp+=sizeof(si_t);
	length+=sizeof(si_t);
	*tmp=0;
	char* length_ptr=tmp;    //��¼���ȵĵ�ַ
	tmp+=sizeof(si_t);
	length+=sizeof(si_t);

	//װ�����
	i=0;
	par_buf_i=0;
	while(-1!=(par_type=get_parameter_type(fun_type,i)))
	{
		if(1==par_type)
		{
			*tmp=par_buf[par_buf_i];
			par_buf_i++;
			length+=sizeof(si_t);
			tmp+=sizeof(si_t);
		}
		else if(2==par_type)      //!!!!�����֮���ٲ���������͵Ĳ���
		{
			*tmp=title;       //????���ܻ�������
			length+=sizeof(char*);
			tmp+=sizeof(char*);
		}
		i++;
	}

	//����д�볤�ȣ�length����ͷ�����ȣ�
	*length_ptr=length;
	ret=send_buffer_to_comm(uds_ptr,buffer,length);
	if(-1==ret)
	{
		EGUI_PRINT_ERROR("comm write error!");
		return ret;
	}
}





static si_t get_parameter_type(int fun_type,int i)
{
	if(i>=10)
	{
		return -1;
	}
	return function_parameter_graph[fun_type].parameter_list[i];
}







static int send_buffer_to_comm(struct egui_uds uds_ptr,char* buf,int length)
{
	if(-1==uds_write(usd_ptr,buf,length))
	{
		EGUI_PRINT_ERROR("cannot write into comm!");
		return -1;
	}
	return 0;
}
