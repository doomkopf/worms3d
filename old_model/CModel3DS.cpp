#include "CModel3DS.h"
#include <gl/gl.h>

CModel3DS::CModel3DS()
{
	loaded=false;
}

bool CModel3DS::Load(char *name)
{
	file1=fopen(name,"rb");
	if(!file1)
		return false;

	while(read_primary_chunk()==0);

	fclose(file1);

	loaded=true;

	return true;
}

int CModel3DS::read_primary_chunk()
{
	unsigned char version;

	if(ReadInt()==0x4d4d)
	{
		fseek(file1,28L,SEEK_SET);
		version=ReadChar();
		if(version<3)
			return 1;
		fseek(file1,16,SEEK_SET);
		read_3ds();
	}
	else
		return 1;

	return 0;
}

int CModel3DS::read_3ds()
{
	WORD id;
	DWORD len;
	bool done=false;

	while(!done)
	{
		id=ReadInt();
		if(feof(file1))
			break;
		len=ReadLong();

		switch(id)
		{
		case 0xffff:
			done=true;
			break;

		case 0x3d3d:
			read_object(len);
			break;

		default:
			unsigned long pos;
			pos=ftell(file1);
			pos+=len-6;
			if(fseek(file1,pos,SEEK_SET))
				done=true;
			break;
		}
		if(feof(file1))
			break;
	}

	return 1;
}

void CModel3DS::read_object(DWORD len)
{
	unsigned long count=ftell(file1)+(len-6);
	bool done=false;
	WORD id;
	DWORD llen;
	int u=0;

	while(!done)
	{
		id=ReadInt();
		if(feof(file1))
			break;
		
		llen = ReadLong();
		
		switch(id)
		{
		case 0x4000:
			char ch;
		
			if(head == NULL)
			{
				head = new mesh_object;
				tail = head;
			}
			else
			{
				tail->next = new mesh_object;
				tail = tail->next;
			}
		
			tail->next = NULL;
			tail->flst = NULL;
			tail->vlst = NULL;
			tail->nf = 0;
			tail->nv = 0;
			tail->mnv = 0;
			tail->mc = NULL;
			tail->fhead = NULL;
			tail->ftail = NULL;
		
			while((ch = fgetc(file1)) != 0)
			{
				tail->name[u] = ch;
				u++;
			}
		
			tail->name[u] = '\0';
			read_mesh(llen);
		
			if(tail->nv == 0)
			{
				if(tail->flst != NULL) delete tail->flst;
				if(tail->vlst != NULL) delete tail->vlst;
				if(tail == head)
				{
					delete tail;
					tail = head = NULL;
				}
				else
				{
					mesh_object *t, *p;
					t = p = head;
					while(t != NULL)
					{
						if(t == tail)
							break;
						else
						{
							p = t;
							t = t->next;
						}
					}
					delete tail;
					tail = p;
					tail->next = NULL;
				}
			}
			break;
		
		case 0xAFFF:
			read_mat(llen);
			break;
	
		default:
			unsigned long pos;
			pos = ftell(file1);
			if((pos - 6) >= count)
			{
				fseek(file1,-6,SEEK_CUR);
				done=true;
				break;
			}
			pos += (llen - 6);
			if(fseek(file1, pos, SEEK_SET))
				done=true;
			break;
		}
	}
}

void CModel3DS::read_mesh(DWORD len)
{
	unsigned long count=ftell(file1)+(len - 6);
	WORD id;
	DWORD llen;
	bool done=false;

	while(!done)
	{
		id=ReadInt();
		if(feof(file1))
			break;
		llen = ReadLong();
		switch(id)
		{
		case 0x4100:
			if(tail == NULL)
				break;
			break;
		
		case 0x4110:
			int i;
			tail->nv = ReadInt();
			tail->vlst = new float[tail->nv * 3];
			for(i=0; tail->nv; i++)
			{
				fread(&tail->vlst[i*3], sizeof(float), 1, file1);
				fread(&tail->vlst[i*3+2], sizeof(float), 1, file1);
				fread(&tail->vlst[i*3+1], sizeof(float), 1, file1);
			} // ERROR
			break;

		case 0x4120:
			unsigned int nf;
			nf = ReadInt();
			tail->nf = nf;
			tail->flst = new WORD[tail->nf * 4];
			for(i=0; nf; i++)
			{
				fread(&(tail->flst[i*4+2]), sizeof(WORD), 1, file1);
				fread(&(tail->flst[i*4+1]), sizeof(WORD), 1, file1);
				fread(&(tail->flst[i*4+0]), sizeof(WORD), 1, file1);
				fread(&(tail->flst[i*4+3]), sizeof(WORD), 1, file1);
			}
			break;
		
		case 0x4130:
			char ch;
			if(tail == NULL)
				break;
			if(tail->fhead == NULL)
			{
				tail->fhead = new face_mat;
				tail->ftail = tail->fhead;
			}
			else
			{
				tail->ftail->next = new face_mat;
				tail->ftail = tail->ftail->next;
			}
			tail->ftail->next = NULL;
			while((ch = fgetc(file1)) != 0)
			{
				tail->ftail->name[i] = ch;
				i++;
			}
			tail->ftail->name[i] = '\0';
			tail->ftail->ne = ReadInt();
			tail->ftail->faces = new WORD[tail->ftail->ne];
			fread(tail->ftail->faces, sizeof(WORD)*tail->ftail->ne,1,file1);
			break;
		
		case 0x4140:
			if(tail == NULL)
				break;
			tail->mnv = ReadInt();
			tail->mc = new float[tail->mnv * 2];
			for(i=0; tail->mnv; i++)
			{
				fread(&(tail->mc[i*2]), sizeof(float), 1, file1);
				fread(&(tail->mc[i*2+1]), sizeof(float), 1, file1);
			}
			break;
		
		case 0x4160:
			int j;
			if(tail == NULL)
				break;
			for (j=0;j<4;j++)
			{
				for (i=0;i<3;i++)
				{
					fread(&(tail->lmat[j][i]),sizeof (float),1,file1);
				}
			}
			tail->lmat[0][3]=0;
			tail->lmat[1][3]=0;
			tail->lmat[2][3]=0;
			tail->lmat[3][3]=1;
			break;
		
		case 0x4000:
			fseek(file1, -6, SEEK_CUR);
			done=true;
			break;

		default:
			unsigned long pos;
			pos = ftell(file1);
			if((pos - 6) >= count)
			{
				fseek(file1, -6, SEEK_CUR);
				done=false;
				break;
			}
			pos+=llen-6;
			if(fseek(file1, pos, SEEK_SET))
				done=false;
			break;
		}
	}
}

void CModel3DS::read_mat(DWORD len)
{
	unsigned long count=ftell(file1)+(len-6);
	WORD id;
	DWORD llen;
	bool done=false;
	BOOL is_ambient = FALSE;
	BOOL is_diffuse = FALSE;
	BOOL is_specular = FALSE;
	int i=0;
	
	if(mathead == NULL)
	{
		mathead = new mat_list;
		mattail = mathead;
	}
	else
	{
		mattail->next = new mat_list;
		mattail = mattail->next;
	}
	mattail->next = NULL;
	mattail->htex = NULL;
	
	while(!done)
	{
		id = ReadInt();
		if(feof(file1))
		{ 
			done=true;
			break;
		}
		llen = ReadLong();
		switch(id)
		{
		case 0xA000:
			char ch;
			mattail->next = NULL;
			while((ch = fgetc(file1)) != 0)
			{
				mattail->name[i] = ch;
				i++;
			}
			mattail->name[i] = '\0';
			break;
		
		case 0xA010:
			is_diffuse = FALSE;
			is_specular = FALSE;
			is_ambient = TRUE;
			mattail->ambient = 0;
			break;
		
		case 0xA020:
			is_diffuse = TRUE;
			is_specular = FALSE;
			is_ambient = FALSE;
			mattail->diffuse = 0;
			break;
		
		case 0xA030:
			is_diffuse = FALSE;
			is_specular = TRUE;
			is_ambient = FALSE;
			mattail->specular = 0;
			break;
		
		case 0xA200:
			if(mattail->htex == NULL)
			{
				mattail->htex = new _map_list;
				mattail->htex->next = NULL;
				mattail->ttex = mattail->htex;
			}
			else
			{
				mattail->ttex->next = new _map_list;
				mattail->ttex = mattail->ttex->next;
				mattail->ttex->next = NULL;
			}
			mattail->ttex->u = mattail->ttex->v = mattail->ttex->uoff = mattail->ttex->voff = 0.0;
			mattail->ttex->rot = 0.0;
			break;
		
		case 0xA300:
			while((ch = fgetc(file1)) != 0)
			{
				mattail->ttex->filename[i] = ch;
				i++;
			}
			mattail->ttex->filename[i] = '\0';
			break;
		
		case 0xA354:
			fread(&(mattail->ttex->v), sizeof(float), 1, file1);
			break;
		
		case 0xA356:
			fread(&(mattail->ttex->u), sizeof(float), 1, file1);
			break;
		
		case 0xA358:
			fread(&(mattail->ttex->uoff), sizeof(float), 1, file1);
			break;
		
		case 0xA35A:
			fread(&(mattail->ttex->voff), sizeof(float), 1, file1);
			break;
		
		case 0xA35C:
			fread(&(mattail->ttex->rot), sizeof(float), 1, file1);
			break;
		
		case 0x0011:
			char r, g, b;
			if(is_diffuse)
			{
				fread(&r, 1, 1, file1);
				fread(&g, 1, 1, file1);
				fread(&b, 1, 1, file1);
				mattail->diffuse = long((r&0xFF)<<16) | long((g&0xFF)<<8) | long(b&0xFF);
			}
			else if(is_ambient)
			{
				fread(&r, 1, 1, file1);
				fread(&g, 1, 1, file1);
				fread(&b, 1, 1, file1);
				mattail->ambient = long((r&0xFF)<<16) | long((g&0xFF)<<8) | long(b&0xFF);
			}
			if(is_specular)
			{
				fread(&r, 1, 1, file1);
				fread(&g, 1, 1, file1);
				fread(&b, 1, 1, file1);
				mattail->specular = long((r&0xFF)<<16) | long((g&0xFF)<<8) | long(b&0xFF);
			}
			break;
		
		default:
			unsigned long pos;
			pos = ftell(file1);
			if((pos - 6) >= count)
			{
				fseek(file1, -6, SEEK_CUR);
				done=true;
				break;
			}
			pos += (llen - 6);
			if(fseek(file1, pos, SEEK_SET))
				done=true;
			break;
		}
	}
}

unsigned char CModel3DS::ReadChar()
{
	return fgetc(file1);
}

unsigned int CModel3DS::ReadInt()
{
	unsigned int temp=ReadChar();
	return (temp | (ReadChar() << 8));
}

unsigned long CModel3DS::ReadLong()
{
	unsigned long temp1,temp2;
	
	temp1=ReadInt();
	temp2=ReadInt();
	
	return (temp1 | (temp2 << 16));
}

CModel3DS::~CModel3DS()
{
	if(loaded)
	{
		delete head;
		delete tail;

		loaded=false;
	}
}

void CModel3DS::Draw()
{
}