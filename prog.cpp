#include <iostream>
#include <fstream>
#include <string>

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

std::cout<<contador<<std::endl;

lista=new Candidato[quantidade];

std::ifstream arquivo2 ("gabarito.txt");
if(arquivo2.is_open()){
	//FAZER A ATRIBUICAO DO ARQUIVO AS VARIAVEIS
	for(long int i=0;i<quantidade;i++){
		getline(arquivo2,lista[i].linhaArquivo);
	}

}else{
	std::cout<<"Erro ao abrir arquivo";
}
arquivo2.close();

std::cout<<lista[0].linhaArquivo<<std::endl;
std::cout<<lista[1].linhaArquivo<<std::endl;
std::cout<<lista[2].linhaArquivo<<std::endl;

return 0;
}