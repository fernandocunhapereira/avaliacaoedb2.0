#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

struct Candidato{
	std::string nome;
	std::string linhaArquivo;
	char respostas[10];
	int nota=0;
};

int main(int argc, char const *argv[]){

std::string linha;
long int quantidade=0;
long int contador=0;
Candidato* lista;

//LEITURA DO ARQUIVO E CONTAGEM DE LINHAS ==================================================
std::ifstream arquivo ("gabarito.txt");
if(arquivo.is_open()){
	while(getline (arquivo,linha)){
		//std::cout << linha << '\n';
		quantidade +=1;
	}
	arquivo.close();
}else{
	std::cout<<"Erro ao abrir arquivo";
} //========================================================================================

std::cout<<"contador "<<contador<<std::endl;
std::cout<<"quantidade de candidatos "<<quantidade<<std::endl;
std::cout<<std::endl;
lista=new Candidato[quantidade];


//ATRIBUICAO DO ARQUIVO NAS VARIAVEIS ======================================================
std::ifstream arquivo2 ("gabarito.txt");

if(arquivo2.is_open()){
	std::string nome;
	char resposta;
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
} //========================================================================================

//std::cout<<lista[0].linhaArquivo<<std::endl;
//std::cout<<lista[1].linhaArquivo<<std::endl;
//std::cout<<lista[2].linhaArquivo<<std::endl;	//IMPRIMIR VARIAVEIS (AINDA EM STRING)
//std::cout<<lista[0].linhaArquivo[7]<<std::endl;

//IMPRIME CADA CARACTER DA STRING, PULA LINHA QUANDO TEM ESPAÇO ===========================
// for(int i=0;i<lista[2].linhaArquivo.size();i++){
// 	if (lista[2].linhaArquivo[i]==' '){
// 		std::cout<<"\n";
// 	}else {
// 		std::cout<<lista[2].linhaArquivo[i];
// 	}
// }
std::cout<<std::endl; //===================================================================

std::cout<<"fim teste"<<std::endl;
return 0;
}