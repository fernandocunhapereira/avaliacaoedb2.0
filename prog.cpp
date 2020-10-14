#include <iostream>
#include <fstream>
#include <string>
//#include <cstring>

struct Candidato{
	std::string nome;
	std::string linhaArquivo;
	char respostas[10];
	int nota=0;
};

struct Questoes{
	long int acertos[10]={0,0,0,0,0,0,0,0,0,0};
	long int brancos[10]={0,0,0,0,0,0,0,0,0,0};
	int numeroQuestoes[10]={1,2,3,4,5,6,7,8,9,10};
};

//============================= INICIO PROGRAMA ===========================
int main(int argc, char const *argv[]){

std::string linha;
long int quantidade=0;
long int contador=0;
Candidato* lista;
Questoes questoes;
char gabarito[10]={'A','B','C','D','E','E','D','C','B','A'};

//LEITURA DO ARQUIVO E CONTAGEM DE LINHAS ==================================
std::ifstream arquivo ("gabarito.txt");
if(arquivo.is_open()){
	while(getline (arquivo,linha)){
		//std::cout << linha << '\n';
		quantidade +=1;
	}
	arquivo.close();
}else{
	std::cout<<"Erro ao abrir arquivo";
} 
//==========================================================================

std::cout<<"contador "<<contador<<std::endl;
std::cout<<"quantidade de candidatos "<<quantidade<<std::endl;
std::cout<<std::endl;

lista=new Candidato[quantidade];

//ATRIBUICAO DADOS DO ARQUIVO TXT NAS VARIAVEIS ============================
std::ifstream arquivo2 ("gabarito.txt");

if(arquivo2.is_open()){
	// std::string nome;
	// char resposta;
	// while(!arquivo2.eof()){
	// 	arquivo2>>nome;
	// 	std::cout<<nome<<"\n";
	// 	for(int i=0;i<10;i++){
	// 		arquivo2>>resposta;
	// 		std::cout<<resposta<<"\n";
	// 	}
	// }
	for(long int i=0;i<quantidade;i++){
		arquivo2>>lista[i].nome;
		std::cout<<lista[i].nome<<"\n";
		for(int j=0;j<10;j++){
			arquivo2>>lista[i].respostas[j];
			std::cout<<lista[i].respostas[j]<<"\n";
		}
	}
	
}else{
	std::cout<<"Erro ao abrir arquivo";
}//=========================================================================

//CALCULO DAS NOTAS DOS ALUNOS =============================================
for(long int i=0;i<quantidade;i++){
	for(int j=0;j<10;j++){
		if(lista[i].respostas[j]==gabarito[j]){
			lista[i].nota +=1; //incrementa nota do aluno
		}
		if(lista[i].respostas[j]!='A' && lista[i].respostas[j]!='B' && lista[i].respostas[j]!='C' && lista[i].respostas[j]!='D' && lista[i].respostas[j]!='E'){
			questoes.brancos[j] +=1; //incrementa brancos na questao j
		}
		if(lista[i].respostas[j]==gabarito[j]){
			questoes.acertos[j] +=1;
		}
	}std::cout<<lista[i].nome<<" nota "<<lista[i].nota<<"\n";
}
//==========================================================================

//TOTAL DE BRANCOS E ACERTOS POR QUESTAO ===================================
std::cout<<"brancos ";
for(int i=0;i<10;i++){
	std::cout<<questoes.brancos[i]<<" ";
}
std::cout<<std::endl;
std::cout<<"acertos ";
for(int i=0;i<10;i++){
	std::cout<<questoes.acertos[i]<<" ";
}
//==========================================================================
std::cout<<std::endl; 
std::cout<<"fim teste"<<std::endl;
return 0;
}