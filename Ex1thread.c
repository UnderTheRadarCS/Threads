#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include <fcntl.h>

void gagnerdutemps()
{

	/*
		Ma VM était trop rapide, même en fermant réouvrant tout le temps le fichier les threads
		n'étaient pas assez ralentis.
		J'ai rajouté ce bete truc à la con pour ralentir encore plus la Vm.
		Totalement facultatif donc.
	*/

	int i = 0,a =1,b =1;

	while (i < 500000 )
	{
		a += b;
		b += a;
		a = 1;
		b = 1;
		i++;
	}

}

/*

    Handler du Thread

*/

void* Fct(void* p)
{

	int *caractere = (int *)malloc(sizeof(int));  // Nbr de fois qu'on tombe sur "Trace"
	*caractere = 0;

	int nbr = 0;
	char buf[5];
	int fichier;
	int nombretabulation = *((int *)p); // recu en argument

	fichier = open("Serveur.cpp",O_RDONLY );

	lseek(fichier,nbr,SEEK_SET);

	while(read(fichier,&buf,sizeof(buf)))
	{

		gagnerdutemps(); // Voir fonction plus haut
		if(strstr(buf,"Trace"))
		{
			for(int i=0;i<nombretabulation;i++)
				printf("	");
			printf("*\n");

			*caractere = *caractere + 1;
		}

		nbr++;

		close(fichier);
		fichier = open("Serveur.cpp",O_RDONLY);

		lseek(fichier,nbr,SEEK_SET);

	}

	pthread_exit(caractere);
}

int main()
{

	int * ret, param = 0,param1=1, param2 = 2, param3 = 3;

	pthread_t tid,tid1,tid2,tid3;

	pthread_create(&tid,NULL,Fct,&param);


	pthread_create(&tid1,NULL,Fct,&param1);


	pthread_create(&tid2,NULL,Fct,&param2);


	pthread_create(&tid3,NULL,Fct,&param3);

	pthread_join(tid,(void**)&ret);
	//printf("le nombre de Trace trouvé est : %d \n\n",(int)*ret);

	pthread_join(tid1,(void**)&ret);
	//printf("le nombre de Trace trouvé est : %d \n\n",(int)*ret);

	pthread_join(tid2,(void**)&ret);
	//printf("le nombre de Trace trouvé est : %d \n\n",(int)*ret);

	pthread_join(tid3,(void**)&ret);
	//printf("le nombre de Trace trouvé est : %d \n\n",(int)*ret);


	free(ret);


	return 1;
}
