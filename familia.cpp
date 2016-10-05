#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>

int main(int argc, char *argv[]){
		// Identificador do processo
	pid_t idProcesso;
	printf("Iniciando o programa\n");
	int idadeFilho1 = 0;
	int idadePai = 0;
	int idadeFilho2 = 0;
	int idadeNeto1 = 0;
	int idadeFilho3 = 0;
	int idadeNeto2 = 0;
	bool fim = false;

	while (idadePai != 18){
		printf("[%d] Sou o processo pai ID: %d\n", idadePai,getpid());
		idadePai++;
		sleep(1);
	}

	printf("[PAI] Alcançou 18 anos... Criado filho1\n");
	
	idProcesso = fork();
	switch(idProcesso){
					// ERRO:
		case -1:
		exit(1);

					//FILHO1
		case 0:
		while(1){
			if(idadeFilho1 == 5){
				printf("[FILHO1] Alcançou 5 anos... Morrendo...\n");
				kill(getpid(), SIGTERM);
			}
			printf("[%d] Sou o processo filho1 ID: %d, pai ID: %d\n", idadeFilho1, getpid(), getppid());
			sleep(1);
			idadeFilho1++;
		}
					//PAI:
		default:
		while(1){
			if(idadePai == 20){
				printf("[PAI] Alcançou 20 anos... Criado filho2\n");
				pid_t idProcesso2 = fork();
				switch(idProcesso2){
									// ERRO:
					case -1:
					exit(1);
									// FILHO2:
					case 0:
					while(1){
						if(idadeFilho2 == 15){
							printf("[FILHO2] Alcançou 15 anos... Criando NETO1...\n");
							pid_t idProcesso3 = fork();

							switch(idProcesso3){
													// ERRO:
								case -1:
								exit(1);
													// NETO1:
								case 0:
								while(1){
									if(idadeNeto1 == 5){
										fim = true;
										printf("[NETO1] Alcançou 5 anos... Morrendo...\n");
										kill(getpid(), SIGTERM);
									}
									printf("[%d] Sou o processo neto1 ID: %d, pai (filho2) ID: %d\n", idadeNeto1, getpid(), getppid());
									sleep(1);
									idadeNeto1++;
								}
							}
						}
						if(idadeFilho2 == 20){
							printf("[FILHO2] Alcançou 20 anos... Morrendo...\n");
							kill(getpid(), SIGTERM);
						}
						printf("[%d] Sou o processo filho2 ID: %d, pai ID: %d\n", idadeFilho2, getpid(), getppid());
						sleep(1);
						idadeFilho2++;
					}
				}
			}
			if(idadePai == 21){
				printf("[PAI] Alcançou 21 anos... Criado filho3\n");
				pid_t idProcesso4 = fork();
				switch(idProcesso4){
									// ERRO:
					case -1:
					exit(1);
									// FILHO3:
					case 0:
					while(1){
						if (idadeFilho3 == 3) {
						    pid_t idProcesso5 = fork();
						    printf("[FILHO3] Alcançou 15 anos... Criando NETO2...\n");
						    switch(idProcesso5){
						    	// ERRO
						    	case -1:
						    		exit(1);
						    	//NETO03;
						    	case 0:
						    		while(1){
											if(idadeNeto2 == 10){
												fim = true;
												printf("[NETO2] Alcançou 10 anos... Morrendo...\n");
												kill(getpid(), SIGTERM);
											}
											printf("[%d] Sou o processo neto2 ID: %d, pai (filho3) ID: %d\n", idadeNeto2, getpid(), getppid());
											sleep(1);
											idadeNeto2++;
										}
						    }
						}
						if(idadeFilho3 == 5){
							printf("[FILHO3] Alcançou 5 anos... Morrendo...\n");
							kill(getpid(), SIGTERM);
						}
						printf("[%d] Sou o processo filho3 ID: %d, pai ID: %d\n", idadeFilho3, getpid(), getppid());
						sleep(1);
						idadeFilho3++;
					}
				}
			}
			if(idadePai == 33){
				printf("[PAI] Alcançou 33 anos... Morrendo...\n");
				kill(getpid(), SIGTERM);
			}
			printf("[%d] Sou o processo pai com ID: %d, pai ID: %d, filho1 ID: %d\n", idadePai, getpid(), getppid(),idProcesso);
			sleep(1);
			idadePai++;
			if(fim) exit(1);
		}
	}
		return 0;
	}