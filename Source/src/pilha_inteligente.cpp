#include "../include/pilha_inteligente.h"

#define DIF_ALTURA 20 // diferenca de altura entre duas cartas
#define CARD_WIDTH 100 // largura final do fundo da pilha
#define CARD_HEIGHT 156 // altura final do fundo da pilha

PilhaInteligente::PilhaInteligente() : Stack<Carta>() {
	this->coord = {0, 0};
	this->stateHover = false;
}

bool PilhaInteligente::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilha.png", renderer, this->coord.x, this->coord.y, 69, 100);
	int w = CARD_WIDTH, h = CARD_HEIGHT;
	if (!SDL_QueryTexture(this->backTexture.getTexture(), NULL, NULL, &w, &h)) {
		return true;
	}
	return false;
}

bool PilhaInteligente::setPosition(SDL_Point pos) {
//	SDL_Point size;
//	SDL_GetWindowSize(gWindow, &size.x, &size.y);

//	if (pos.x > 0 && pos.y > 0 && pos.x + CARD_WIDTH < size.x && pos.y + CARD_HEIGHT < size.y) {
		this->coord = pos;
		this->backTexture.setPosition(this->coord);

		this->organize();

		return true;
//	}
//	return false;
}

SDL_Point PilhaInteligente::getPosition() const {
	return this->coord;
}

//TODO:Tentar implementacao com algorithm::random_shuffle()
//TODO:Tentar implementacao com o algoritmo fisher-yates
void PilhaInteligente::randomize() {
//	random_device seed;
//	srand(seed());
//	int iter = rand()%(MAX_ITER_RANDOM-MIN_ITER_RANDOM)+MIN_ITER_RANDOM;
//	while (iter > 0) {
//		int it1 = rand()%size+1;
//		Node<Carta>* elem = &header;
//		while (it1 > 0) {
//			elem = elem->dir;
//			it1--;
//		}
//		Node<Carta> aux = *elem;
//		elem->dir->esq = aux.esq;
//		elem->esq->dir = aux.dir;
//		elem->dir = &header;
//		elem->esq = header.esq;
//		header.esq->dir = elem;
//		header.esq = elem;
//		iter--;
//	}
}

//}
/*{
	// Alynva: aguardando a implementa��o da sobrecarga do operador []
	srand(time(0));
	int S = this->getSize(), in, out;
	for (int i = 0; i < (rand() % (S * 10) + 50); i++) {
		do {
			in = rand() % S;
			out = rand() % S;
		} while(in == out);
		Carta aux = stack[out];
		stack[out] = stack[in];
		stack[in] = aux;
	}
}*/

void PilhaInteligente::render() {
	this->backTexture.render();

	Stack<Carta> p_temp;
	Carta c_temp;

	while (!this->isEmpty()) {
		this->pop(c_temp);
		p_temp.push(c_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(c_temp);
		c_temp.render();
		this->push(c_temp);
	}
}

void PilhaInteligente::organize() {
	Stack<Carta> p_temp;
	Carta c_temp;

	int y = 0;
	while (!this->isEmpty()) {
		this->pop(c_temp);
		p_temp.push(c_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(c_temp);
		c_temp.setPosition({this->coord.x, this->coord.y + y});
		y += DIF_ALTURA;
		this->push(c_temp);
	}
}

bool PilhaInteligente::isInside(SDL_Point point) {
	SDL_Point position = this->backTexture.getPosition();
//	SDL_Log("P %i %i", position.x, position.y);
	SDL_Point size = this->backTexture.getSize();

	bool inside = ((point.x > position.x && point.x < position.x + size.x) &&
		(point.y > position.y && point.y < position.y + size.y));
	
	Node<Carta>* element = this->peek().dir;
	for (int i = 0; i < this->getSize(); i++) {
		element = element->dir;
		inside = inside || element->value.isInside(point);
	}
	
	// Alynva: N�O FUNCIONOU ISSO
//	for (int i = 0; i < this->getSize(); i++) {
//		inside = inside || this[1].isInside(point);
//	}

	return inside;
}

//Faz a verificacao de naipes para dizer se duas cartas sao da mesma cor
bool PilhaInteligente::isDifferentColor(Carta c1, Carta c2) const {
	if ((c1.getSuit() == 'A' || c1.getSuit() == 'C') && (c2.getSuit() == 'A' || c2.getSuit() == 'C'))
		return true;
		
	else if ((c1.getSuit() == 'B' || c1.getSuit() == 'D') && (c2.getSuit() == 'B' || c1.getSuit() == 'D'))
		return true;

	return false;
}

//P[x] deve retornar o node da posicao x, nao a carta da posicao x, que eh P[x]->getElement()
Node<Carta>* PilhaInteligente::operator[](int index) {
	if (size > index && index >= 0) {
		Node<Carta>* returnNode = header.dir;
		while (index > 0) {
			returnNode = returnNode->dir;
			index--;
		}
		return returnNode;
	}
	return nullptr;
}

void PilhaInteligente::setStateHover(bool state) {
	this->stateHover = state;
}

bool PilhaInteligente::canBeMoved(const Carta * c) const {
	bool isDifferent = false;
	int i;
	for (i = 0; i < this->getSize(); i++) {
		if (this[i].value == c) {
			isDifferent = true;
			break;
		}
	}
	while (i < this->getSize() - 1 && isDifferent) {
		isDifferent = this->isDifferentColor(this[i].value, this[i+1].value);
		i++;
	}
	return isDifferent;
}
