#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

struct id{
    char nome[20];
    char sobrenome[30];
    char apelido[20];
};

struct fone{
    char tipo[10];
    int numero;
};

struct end{
    char email[30];
    char residencial[50];
    char trabalho[50];
};

struct contato{
    struct id pessoaID;
    struct fone pessoaF;
    struct end pessoaE;
    struct contato *prox;
    struct contato *ant;
};
typedef struct contato Contato;

void mostrarRapido(Contato *l)
{
	printf("\n - - - - - - - - - - - AGENDA - - - - -  - - - - - - -\n");
	if(l == NULL)
	{
		printf("\nAgenda vazia.\n");
		return;
	}

	Contato *p;

	for (p = l; p != NULL; p = p->prox) {
		
		printf("\t\t\t");
		puts(p -> pessoaID.nome);
		printf("  - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	}
}

Contato *alterar(Contato *l, int j, char nom[20])//j é a opçao q o usuario desejar alterar
{
	Contato *p;
	int x;
	
	system("cls");
	if(j == 1)
	{
		char nome[20];

		printf("Digite o novo nome.\n");
		fflush(stdin);
		gets(nome);
		for(p = l; p != NULL; p = p -> prox)
		{
		    x = strcmp(p -> pessoaID.nome, nom);//vejo se tem o nome na lista
			if(x == 0)
			{
				strcpy(p -> pessoaID.nome, nome);//coloco o novo nome no contato
				if(p -> ant == NULL && p -> prox == NULL)//quand ah so um contato, ent so retorno ele.
                {
                    return l;
                }

				else if(p -> prox == NULL)//ver se esta no final da lista.
				{
				    Contato *aux;
				    for(aux = p -> ant; aux != NULL; aux = aux -> ant)
                    {
                        if(p -> pessoaID.nome[0] == aux -> pessoaID.nome[0])
                        {
                            if(p -> pessoaID.nome[1] == aux -> pessoaID.nome[1])
                            {
                                p -> ant -> prox = NULL;
                                p -> prox = aux;
                                p -> ant = NULL;
                                aux -> ant = p;
                                return p;
                            }
                            else{
                                p -> ant -> prox = NULL;
                                p -> ant = aux;
                                p -> prox = aux -> prox;
                                aux -> prox = p;
                                return l;
                            }
                        }

                        else if(p -> pessoaID.nome[0] > aux -> pessoaID.nome[0])//quando o caracter do novo nome for maior que o caracter daquela posicao da lista
                            //dai ele vai entra na frente do mesmo.
                        {
                            if(p -> prox == NULL)
                            {
                                return l;
                            }
                            else
                            {
                                p -> ant -> prox = p -> prox;
                                p -> ant = aux;
                                p -> prox = aux -> prox;
                                aux -> prox -> ant = p;
                                aux -> prox = p;
                                return l;
                            }

                        }
                        else if(aux -> ant == NULL)//quando o aux percorre toda a lista e n consegue comparar e o novo nome tem um caracter menor q todos, logo colocaremos
                        //ele na primeira posição.
                        {
                            p -> ant -> prox = p -> prox;
                            p -> prox = aux;
                            aux -> ant = p;
                            p -> ant = NULL;
                            return p;
                        }
                    }
				}

				else if(p -> ant == NULL)//quando o novo nome esta no começo da lista, temos q percorrer toda a lista para encontrar onde ele sera alterado;
                {
                    Contato *aux, *novo;//este novo sera para qnd o vetor na primeira posicao for alterado.
                    for(aux = p -> prox; aux != NULL; aux = aux -> prox)
                    {
                        if(p -> pessoaID.nome[0]  < aux -> pessoaID.nome[0])
                        {
                            if(aux -> prox == NULL)//para o fim da lista
                            {
                                novo = p -> prox;
                                p -> prox -> ant = NULL;
                                p -> prox = aux;
                                p -> ant = aux -> ant;
                                aux -> ant -> prox = p;
                                aux -> ant = p;
                                return novo;
                            }

                            else//no meio
                            {
                                novo = p -> prox;
                                p -> ant = aux -> ant;
                                p -> prox -> ant = NULL;
                                p -> prox = aux;
                                aux -> ant -> prox = p;
                                aux -> ant = p;
                                return novo;
                            }
                        }
                        else if(p -> pessoaID.nome[0] == aux -> pessoaID.nome[0])
                        {
                            if(aux -> prox == NULL)//qnd esta no fim mas n tem mais um prox
                            {
                                return p;
                            }

                            else if(aux -> ant == p)//qnd eh igual ao anterior, logo n muda nd
                            {
                                return aux;
                            }

                            else
                            {
                                novo = p -> prox;
                                p -> prox -> ant = NULL;
                                p -> prox = aux;
                                p -> ant = aux -> ant;
                                aux -> ant -> prox = p;
                                aux -> ant = p;
                                return novo;
                            }
                        }
                        if(aux -> prox == NULL)//para o fim da lista
                        {
                            novo = p -> prox;
                            p -> prox -> ant = NULL;
                            p -> ant = aux;
                            p -> prox = NULL;
                            aux -> prox = p;
                            return novo;
                        }
                    }
                }

                else if(p -> pessoaID.nome[0] > p -> ant -> pessoaID.nome[0])//no meio q tem q ir para o lado direito
                {
                    Contato *aux;
                    for(aux = p -> prox; aux != NULL; aux = aux -> prox)
                    {
                        if(p -> pessoaID.nome[0]  < aux -> pessoaID.nome[0])
                        {
                            if(aux -> prox == NULL)//para o fim da lista
                            {
                                p -> ant -> prox = aux;
                                p -> prox = NULL;
                                aux -> ant = p -> ant;
                                p -> ant = aux;
                                aux -> prox = p;
                                return l;
                            }

                            else//no meio
                            {
                                p -> ant = aux -> ant;
                                p -> prox -> ant = NULL;
                                p -> prox = aux;
                                aux -> ant -> prox = p;
                                aux -> ant = p;
                                return l;
                            }
                        }

                        else if(aux -> prox == NULL)//quando pedi para mudar o antipenultimo e ele eh maior q todos
                        {
                            p -> ant -> prox = aux;
                            p -> prox = NULL;
                            aux -> ant = p -> ant;
                            p -> ant = aux;
                            aux -> prox = p;
                            return l;
                        }

                        else if(p -> pessoaID.nome[0] == aux -> pessoaID.nome[0])
                        {
                            if(aux -> prox == NULL)//qnd esta no fim mas n tem mais um prox
                            {
                                return p;
                            }

                            else if(aux -> ant == p)
                            {
                                return aux;
                            }

                            else
                            {
                                p -> prox -> ant = NULL;
                                p -> prox = aux;
                                p -> ant = aux -> ant;
                                aux -> ant -> prox = p;
                                aux -> ant = p;
                                return l;
                            }
                        }
                    }
                }
                else
                {
                    Contato *aux;
				    for(aux = p -> ant; aux != NULL; aux = aux -> ant)
                    {
                        if(p -> pessoaID.nome[0] == aux -> pessoaID.nome[0])
                        {
                            if(p -> pessoaID.nome[1] == aux -> pessoaID.nome[1])
                            {
                                return l;
                            }
                            return l;
                        }

                        else if(p -> pessoaID.nome[0] > aux -> pessoaID.nome[0])//quando o caracter do novo nome for maior que o caracter daquela posicao da lista
                            //dai ele vai entra na frente do mesmo.
                        {
                            p -> ant -> prox = p -> prox;
                            p -> ant = aux;
                            p -> prox = aux -> prox;
                            aux -> prox -> ant = p;
                            aux -> prox = p;
                            return l;
                        }
                        else if(aux -> ant == NULL)//quando o aux percorre toda a lista e n consegue comparar e o novo nome tem um caracter menor q todos, logo colocaremos
                        //ele na primeira posição.
                        {
                            p -> ant -> prox = p -> prox;
                            p -> prox = aux;
                            aux -> ant = p;
                            p -> ant = NULL;
                            return p;
                        }
                    }
                }
			}
		}

    return l;
	}

	else if(j == 2)
	{
		char sobrenome[30];
		int x;

		printf("Digite o novo sobrenome.\n");
		fflush(stdin);
		gets(sobrenome);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				strcpy(p -> pessoaID.sobrenome, sobrenome);
				return l;
			}
		}
	}
	else if(j == 3)
	{
		char apelido[30];

		printf("Digite o novo apelido.\n");
		fflush(stdin);
		gets(apelido);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				strcpy(p -> pessoaID.apelido, apelido);
				return l;
			}
		}
	}
	else if(j == 5)
	{
		int num;

		printf("Digite o novo numero.\n");
        scanf("%d",&num);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				p->pessoaF.numero = num;
				return l;
			}
		}
	}
	else if(j == 4)
	{
		char tipo[30];

		printf("Digite o novo tipo.\n");
		fflush(stdin);
		gets(tipo);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				strcpy(p -> pessoaF.tipo, tipo);
				return l;
			}
		}
	}
	else if(j == 6)
	{
		char email[30];

		printf("Digite o novo email.\n");
		fflush(stdin);
		gets(email);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				strcpy(p -> pessoaE.email, email);
				return l;
			}
		}
	}
	else if(j == 7)
	{
		char residencial[30];

		printf("Digite o novo residencial.\n");
		fflush(stdin);
		gets(residencial);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				strcpy(p -> pessoaE.residencial, residencial);
				return l;
			}
		}
	}
	else if(j == 8)
	{
		char trabalho[50];

		printf("Digite o novo trabalho.\n");
		fflush(stdin);
		gets(trabalho);
		for(p = l; p != NULL; p = p -> prox)
		{
			x = strcmp(nom, p -> pessoaID.nome);
			if(x == 0)
			{
				strcpy(p -> pessoaE.trabalho, trabalho);
				return l;
			}
		}
	}

    return l;

}

Contato *inserir(Contato *l)
{
	system("cls");
    Contato *p, *novo = (Contato*) malloc(sizeof(Contato));
    
    printf("\n - - - - - - - Inserir contato - - - - - - - \n\n");

    printf("Digite os seguintes dados:\nnome\n");
    fflush(stdin);
    gets(novo -> pessoaID.nome);

    printf("sobrenome\n");
    fflush(stdin);
    gets(novo -> pessoaID.sobrenome);

    printf("apelido\n");
    fflush(stdin);
    gets(novo -> pessoaID.apelido);

    printf("tipo\n");
    fflush(stdin);

    gets(novo -> pessoaF.tipo);

    printf("numero\n");
    scanf("%d",&novo -> pessoaF.numero);

    printf("email\n");
    fflush(stdin);
    gets(novo -> pessoaE.email);

    printf("residencial\n");
    fflush(stdin);
    gets(novo -> pessoaE.residencial);

    printf("trabalho\n");
    fflush(stdin);
    gets(novo -> pessoaE.trabalho);

    if(l == NULL)//ver se não ha nd na list.
    {
    	novo -> prox = NULL;
		novo -> ant = NULL;
	}

	else
	{
		for(p = l; p != NULL; p = p -> prox)
		{
			if(novo -> pessoaID.nome[0] == p -> pessoaID.nome[0])//vejo se as primeiras letras sao iguais
			{
				if(novo -> pessoaID.nome[1] == p -> pessoaID.nome[1])//confiro se a segunda letra tbm eh igual
				{
					if(p -> prox == NULL && p -> ant == NULL)//quando tem 1 elemento na lista
					{
                        novo -> prox = p;
                        p -> ant = novo;
                        return novo;
					}

					else if(p -> prox == NULL)//no final da lista
					{
                        novo -> ant = p;
                        p -> prox = novo;
					return novo;
					}

                    else if(p -> ant == NULL)//no comeco da lista
                    {
                        novo -> prox = p;
                        p -> ant = novo;
                        return novo;
                    }
					else
					{
                        novo -> prox = p;// no meio
                        novo -> ant = p -> ant;
                        p -> ant -> prox = novo;
                        p -> ant = novo;
                        return l;
					}
				}
				else //se a segunda n for igual
				{
					if(novo -> pessoaID.nome[1] < p -> pessoaID.nome[1])
					{
						if(p -> prox == NULL && p -> ant == NULL)//quando tem 1 elemento na lista
						{
							novo -> prox = p;
							p -> ant = novo;
							return novo;
						}

						if(p -> prox == NULL)//no final da lista
						{
							novo -> ant = p -> ant;
							novo -> prox = p;
							p -> ant -> prox = novo;
							p -> ant = novo;
							return l;
						}

						else if(p -> ant == NULL)//vai no comeco da lista
                        {
           		            novo -> prox = p;
                            novo -> ant = NULL;
                            p -> ant = novo;
                            return novo;
                       	}

						else
						{
							novo -> prox = p;//no meio
							novo -> ant = p -> ant;
							p -> ant -> prox = novo;
							p -> ant = novo;
							return l;
						}
					}

					else
					{
						if(p -> prox == NULL && p -> ant == NULL)//quando tem 1 elemento na lista
						{
							novo -> ant = p;
							p -> prox = novo;
							return l;
						}

						if(p -> prox == NULL)//no final da lista
						{
							novo -> ant = p;
							p -> prox = novo;
							return l;
						}

                        else if(p -> ant == NULL)//no comeco da lista
                        {
                            novo -> ant = p;
                            novo -> prox = p -> prox;
                            p -> prox -> ant = novo;
                            p -> prox = novo;
                            return l;
                        }

						else
						{
							novo -> ant = p;//no meio
							novo -> prox = p -> prox;
							p -> prox -> ant = novo;
							p -> prox = novo;
							return l;
						}
					}
				}
			}
			else if(novo -> pessoaID.nome[0] < p -> pessoaID.nome[0])//quand sao letras diferentes vou andando ate achar uma letra maior do novo contato.
			{
				if(p -> prox == NULL && p -> ant == NULL)//quando tem 1 elemento
				{
					novo -> prox = p;
					p -> ant = novo;
					return novo;
				}

				else if(p -> prox == NULL)//para o fim da lista
				{
					novo -> prox = p;
					novo -> ant = p -> ant;
					p -> ant -> prox = novo;
					p -> ant = novo;
					return l;
				}
                else if(p -> ant == NULL)// no começo da lista
                {
                    novo -> prox = p;
                    novo -> ant = NULL;
                    p -> ant = novo;
                    return novo;
                }

				else //no meio
				{
					novo -> ant = p -> ant;
					novo -> prox = p;
					p -> ant -> prox = novo;
					p -> ant = novo;
					return l;
				}

			}
			else if(p -> prox == NULL)//para letras que irão no fianl, sendo assim, sendo a maior
			{
				novo -> ant = p;
				novo -> prox = NULL;
				p -> prox = novo;
				return l;
			}
		}
	}
	return novo;
}

Contato* retira (Contato* c, Contato* p) {

   if(p -> prox == NULL && p -> ant == NULL)
    {
        free(p);
        c = NULL;
        return c;
    }

    else if (c == p)
    {
        c = p->prox;
        c->ant=NULL;
        return c;
    }

    else{
        p->ant->prox = p->prox;
    }

   if (p->prox != NULL)
   {
         p->prox->ant = p->ant;
   }

    free(p);
    return c;
}

void mensagem(char nom[20])
{
    char mensagem[200];
    int x, y, z, a, b;
    system("cls");
    printf("Ola, eu sou ");
    puts(nom);

    fflush(stdin);
    gets(mensagem);
    strlwr(mensagem);

    x = strncmp(mensagem, "oi", 2);
    y = strncmp(mensagem, "ola", 3);
    z = strncmp(mensagem, "blz", 3);
    a = strncmp(mensagem, "eae", 3);
    b = strncmp(mensagem, "fmz", 3);
    if(x == 0||y == 0||z == 0||a == 0||b == 0)
    {
        printf("Estou muito bem, obrigado por perguntar. Voce gostou da agenda?\n");
        fflush(stdin);
        gets(mensagem);
        strlwr(mensagem);
		x = strncmp(mensagem, "sim", 3);
		y = strncmp(mensagem, "aham", 4);
		z = strncmp(mensagem, "uhum", 4);
		a = strncmp(mensagem, "mais", 4);
        if(x == 0||y == 0||z == 0||a == 0)
        {
            printf("Eu tbm gostei, da ate para mandar mensagens um para o outro kkk\nQue time voce torce?\n");
            fflush(stdin);
            gets(mensagem);
            strlwr(mensagem);
			x = strncmp(mensagem, "santos", 6);
			y = strncmp(mensagem, "inter", 5);
			z = strncmp(mensagem, "gremio", 6);
			a = strncmp(mensagem, "colorado", 8);
			b = strncmp(mensagem, "tricolor", 8);

            if(x == 0||y == 0||z == 0|| a == 0||b == 0)
            {
                printf("Que legal, eu sou santista! Poderiamos marcar para ver um jogo da selecao, depois nos falamos por mensagem, ate mais!\n\n");
            }
            else
            {
                printf("N conheco esse time, ele eh de q regiao do Brasil?\n");
                fflush(stdin);
                gets(mensagem);

                z = strncmp(mensagem, "nor", 3);
                a = strncmp(mensagem, "su", 2);
                b = strncmp(mensagem, "centroeste", 11);
                if(z == 0 || a == 0 || b == 0)
                {
                    printf("massa, legal eu n conhecia\nVc mora em santa maria?\n");
                    fflush(stdin);
                    gets(mensagem);
                    strlwr(mensagem);

                    x = strncmp(mensagem, "sim", 3);
                    y = strncmp(mensagem, "s", 1);
                    z = strncmp(mensagem, "aham", 4);

                    if(x == 0||y == 0||z == 0)
                    {
                        printf("eu tbm! podemos marcar para assistir um jogo do seu time e tomar uma gelada kkk\nNos falamos ent, ate mais\nzn");
                        return;
                    }
                    else
                    {
                        printf("baah tche! que massa, tenho conhecidos ai, preciso sair, dps nos falamos, ate mais o/ \n\n");
                        return;
                    }
                }
                else
                {
                    printf("nunca ouvi falar desta regiao kkk\n preciso sair, dps nos falamos, xau!\n\n");
                    return;
                }
            }

        }
        else
        {
            printf("baah eu achei legal, vc vai se acostumar, eh mais organizado q o wpp UHSAHUSAUHSAUs\nvc achou um problema na agenda?\n");
            fflush(stdin);
            gets(mensagem);
            strlwr(mensagem);

            x = strncmp(mensagem, "sim", 3);
            y = strncmp(mensagem, "s", 1);
            z = strncmp(mensagem, "aham", 4);

            if(x == 0||y == 0||z == 0)
            {
                printf("tbm achei um erro, mas eh normal, este app de agenda esta no BETA. Tenho q sair, dps nos falamos, ate\n\n");
                return;
            }
            else
            {
                printf("eu tbm n achei, so o plano de fundo preto q eh um pouco feio, mas logo logo chegara a versao final do app, esta no BETA. Tenho q sair, ate mais.\n\n");
                return;
            }
        }
    }

    else
    {
        printf("Nao entendi oque vc digitou, digite de uma forma mais clara, sou iniciante em SMS kkkk\nEm que regiao do Brasil vc esta morando atualmente?\n");
        fflush(stdin);
        gets(mensagem);
        strlwr(mensagem);

		z = strncmp(mensagem, "nor", 3);
		a = strncmp(mensagem, "su", 2);
		b = strncmp(mensagem, "centroeste", 11);

        if(z == 0 ||a == 0|| b == 0)
        {
            printf("Que legal! Eu estou morando na regiao Sul atualmente. Dps nos falamos, ate.\n\n");
            return;
        }
        else
        {
        	printf("Eu acho q esta regiao n existe kkk, dps nos falamos, ate. \n\n");
            return;
		}
    }
}

main()
{
	Contato *c = NULL;
	int  i, menu;
	char opc = 's';

	while(opc == 's')
	{
		system("cls");
		mostrarRapido(c);

		printf("1 - Inserir contato\n2 - Alterar\n3 - Excluir\n4 - Pesquisar\n5 - Mensagem\n\n");
		scanf("%d",&menu);

		if(menu == 1)
		{
			c = inserir(c);
			system("cls");
			printf("\n - - - REGISTRANDO CONTATO - - - \n\n");
			sleep(1);
			system("cls");
		}

		else if(menu == 2)
		{
			system("cls");
			
		    int y = 0; //se ele for > 0 ele indicara que entro no if i == 0, se for igual qr dizer q ele n entrou e o nome n exxiste na lista;
			char no[20], alter;//alter é uma variavel de opção para alterar, se ele desejar continuar
			printf("Digite quem deseja alterar.(nome)\n");//verifo pelo nome se a pessoa existe
			fflush(stdin);
			gets(no);

            strlwr(no);
			Contato *p;

			for(p = c; p != NULL; p = p -> prox)
			{
				printf("\n - - -ALTERAR - - - \n\n");
				i = strcmp(no, p -> pessoaID.nome);//uso o strcmp para conferir se existe na lista de contatos aquele nome

                if(i == 0)
                {
                	system("cls");
                    y++;
                    printf("Deseja alterar:\n1 - Nome\n2 - Sobrenome\n3 - Apelido\n4 - Tipo\n5 - Numero\n6 - Email\n7 - Residencial\n8 - Trabalho\n");//ver oq deseja alterar.
                    scanf("%d",&i);

                    c = alterar(c, i, no);

                    do{
                        printf("deseja alterar outra coisa?<s / n>\n");
                        fflush(stdin);
                        scanf("%c",&alter);

                        strlwr(&alter);

                        if(alter == 's')
                        {
                        	system("cls");
                        	printf("\n - - -ALTERAR - - - \n\n");
                        	printf("\n1 - Nome\n2 - Sobrenome\n3 - Apelido\n4 - Tipo\n5 - Numero\n6 - Email\n7 - Residencial\n8 - Trabalho\n");//ver oq deseja alterar.
                            printf("Digite a opcao do menu que deseja alterar.\n");
                            scanf("%d",&i);

                            c = alterar(c, i, no);
                        }
                    }while(alter == 's');
                    printf("\n - - Alterando Contato - - \n");
                    sleep(2);
                    system("cls");
                }
			}
            if(y == 0)
            {
                printf("Nome não existe na agenda.\n");
            }
            system("cls");
		}

		else if(menu == 3)
        {
        	system("cls");
            char nomep[20];
            int x, y = 0;//y = auxiliar.
            Contato *p;
            printf("Digite o nome que deseja excluir:");
            fflush(stdin);
            gets(nomep);
            printf("\n");
            for(p = c; p != NULL; p=p->prox)
            {
                x=strcmp(nomep,p->pessoaID.nome);
                if(x == 0)
                {
                     c = retira(c,p);
                     y++;
                }
            }
            if(y==0){
                printf("Nao encontrado.\n");
                sleep(2);
            }
         system("cls");           
        }

        else if(menu == 4)
        {
        	system("cls");
            char nomep[20];
            int x;
            Contato *p;
            printf("1 - Nome\n2 - Telefone \n");
            scanf("%d", &menu);
            system("cls");
            if(menu == 1)
            {
                printf("Digite o nome que deseja pesquisar:");
                fflush(stdin);
                gets(nomep);
                printf("\n");
                for(p = c; p != NULL; p=p->prox)
                {
                    x=strcmp(nomep,p->pessoaID.nome);
                    if(x == 0)
                    {
                        printf("\nNome: ");
                        puts(p->pessoaID.nome);

                        printf("Sobrenome: ");
                        puts(p->pessoaID.sobrenome);

                        printf("Apelido: ");
                        puts(p->pessoaID.apelido);

                        printf("Tipo: ");
                        puts(p->pessoaF.tipo);

                        printf("Numero: %d\n",p->pessoaF.numero);

                        printf("Email: ");
                        puts(p->pessoaE.email);

                        printf("Residencial: ");
                        puts(p->pessoaE.residencial);

                        printf("Trabalho: ");
                        puts(p->pessoaE.trabalho);
                    }
                    else {
                        printf("Esse nome nao possui na agenda!\n");
                    }
                }
                printf("\n");

            }
            else if(menu == 2)
            {
                int telpesq;
                printf("Digite o telefone que voce deseja pesquisar:");
                scanf("%d",&telpesq);
                printf("\n");

                for(p=c; p !=NULL; p=p->prox)
                {

                    if(telpesq == p->pessoaF.numero)
                    {
                        printf("Nome: ");
                        puts(p->pessoaID.nome);

                        printf("Sobrenome: ");
                        puts(p->pessoaID.sobrenome);

                        printf("Apelido: ");
                        puts(p->pessoaID.apelido);

                        printf("Tipo: ");
                        puts(p->pessoaF.tipo);

                        printf("Numero: %d\n",p->pessoaF.numero);

                        printf("Email: ");
                        puts(p->pessoaE.email);

                        printf("Residencial: ");
                        puts(p->pessoaE.residencial);

                        printf("Trabalho: ");
                        puts(p->pessoaE.trabalho);
                    }
                    else{
                        printf("Esse numero nao possui na agenda!\n");
                    }
                }

                printf("\n");
            }
			system("pause");
			system("cls");
        }

        else if(menu == 5)
        {
        	system("cls");
        	Contato *p;
        	int x, y = 0;
        	
            char nomee[20];
            mostrarRapido(c);
            printf("Qual nome deseja mandar a msg?\n");
            fflush(stdin);
            gets(nomee);
            strlwr(nomee);
            
			for(p = c; p != NULL; p=p->prox)
            {
                x=strcmp(nomee,p->pessoaID.nome);
                if(x == 0)
                {
                    mensagem(nomee);
                    y++;
                }
                
            }		
			if(y == 0)
			{
				printf("Nome nao existe.\n");
				sleep(1.8);
			}
			system("pause");
	       system("cls");
        }
		printf("Deseja continuar na agenda?\n");
		fflush(stdin);
		scanf("%c",&opc);
	}
	free(c);
}


