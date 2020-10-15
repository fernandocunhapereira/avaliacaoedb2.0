#include <iostream>
#include <fstream>
#include <string>

struct Candidato{
	std::string nome;
	std::string linhaArquivo;
	char respostas[10];
	int nota=0;
};

struct Questoes{
	long int acertos[10]={0,0,0,0,0,0,0,0,0,0};
	long int brancos[10]={0,0,0,0,0,0,0,0,0,0};
	int numeroQuestoes[10]={1,2,3,4,5,6,7,8,9,10}; //vetor para identificar o numero das questoes quando os vetores acertos e brancos forem ordenados
};


//============================= INICIO PROGRAMA ===========================
int main(int argc, char const *argv[]){

std::string linha;
long int quantidade=0;
long int contador=0;
Candidato* lista;
Questoes questoes;
char gabarito[10]={'A','B','C','D','E','E','D','C','B','A'};
std::string nomeArquivo=argv[1];
std::string funcao=argv[2];
int ranking=std::atoi(argv[3]);

//RECEBER ARQUIVO GABARITO TXT E ATRIBUIR NO VETOR GABARITO ================
if(argv[4]!=NULL){
	std::string nomeGabarito=argv[4];
	std::ifstream arquivo3(nomeGabarito);
	if(arquivo3.is_open()){
		for(int i=0;i<10;i++){
			arquivo3>>gabarito[i];
		}
	}else{
		std::cout<<"Erro ao abrir arquivo\n";
	}
}

//==========================================================================

//LEITURA DO ARQUIVO E CONTAGEM DE LINHAS ==================================
std::ifstream arquivo (nomeArquivo); 
if(arquivo.is_open()){
	while(getline (arquivo,linha)){
		//std::cout << linha << '\n';
		quantidade +=1;
	}
	arquivo.close();
}else{
	std::cout<<"Erro ao abrir arquivo\n";
} 
//==========================================================================

lista=new Candidato[quantidade];

//ATRIBUICAO DADOS DO ARQUIVO TXT NAS VARIAVEIS ============================
std::ifstream arquivo2 (nomeArquivo);

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
		//std::cout<<lista[i].nome<<"\n";
		for(int j=0;j<10;j++){
			arquivo2>>lista[i].respostas[j];
			//std::cout<<lista[i].respostas[j]<<"\n";
		}
	}
	
}else{
	std::cout<<"Erro ao abrir arquivo\n";
}
//=========================================================================

//CALCULO DAS NOTAS DOS ALUNOS; BRANCOS E ACERTOS POR QUESTAO ==============
for(long int i=0;i<quantidade;i++){
	for(int j=0;j<10;j++){
		if(lista[i].respostas[j]==gabarito[j]){
			lista[i].nota +=1; //incrementa nota do aluno
		}
		if(lista[i].respostas[j]!='A' && lista[i].respostas[j]!='B' && lista[i].respostas[j]!='C' && lista[i].respostas[j]!='D' && lista[i].respostas[j]!='E'){
			questoes.brancos[j] +=1; //incrementa brancos por questao 
		}
		if(lista[i].respostas[j]==gabarito[j]){
			questoes.acertos[j] +=1; //incrementa acertos por questao
		}
	}std::cout<<lista[i].nome<<" nota "<<lista[i].nota<<"\n";
}
//==========================================================================

//IMPRIMIR TOTAL DE BRANCOS E ACERTOS POR QUESTAO ==========================
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

//LISTAR RANKING DOS MELHORES ALUNOS =======================================
if(funcao=="best"){
   	for(long int i=0;i<quantidade-1;++i){
    	int min=i;
    	for(long int j=i+1;j<quantidade;++j){
    		if(lista[min].nota>lista[j].nota){
    			min=j;
    		}	
    	}
    Candidato temp=lista[i];
    lista[i]=lista[min];
    lista[min]=temp;     	
	}
	for(long int i=quantidade-1;i>=quantidade-ranking;i--){
		std::cout<<lista[i].nome<<"\n";
	}
}
//==========================================================================
if(funcao=="worst"){
   	for(long int i=0;i<quantidade-1;++i){
    	int min=i;
    	for(long int j=i+1;j<quantidade;++j){
    		if(lista[min].nota>lista[j].nota){
    			min=j;
    		}	
    	}
    Candidato temp=lista[i];
    lista[i]=lista[min];
    lista[min]=temp;     	
	}
	for(long int i=0;i<ranking;i++){
		std::cout<<lista[i].nome<<"\n";
	}
}



//IMPRESSAO DE ALGUMAS VARIAVEIS ===========================================
std::cout<<std::endl;
std::cout<<"contador "<<contador<<std::endl;
std::cout<<"quantidade de candidatos "<<quantidade<<std::endl;
std::cout<<"nome do arquivo "<<nomeArquivo<<std::endl;;
std::cout<<"nome da funcao "<<funcao<<std::endl;
std::cout<<"ranking "<<ranking<<std::endl;
if(argv[4]!=NULL){
	std::cout<<"com arquivo gabarito"<<std::endl;
}else{
	std::cout<<"sem arquivo gabarito"<<std::endl;
}
for(int i=0;i<10;i++){
	std::cout<<gabarito[i]<<" ";	
}
std::cout<<std::endl;
std::cout<<"fim teste"<<std::endl;
//==========================================================================

delete[] lista;
return 0;
}