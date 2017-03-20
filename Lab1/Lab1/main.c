//
// Dwukierunkowa lista, której elementy s¹ listami dwukierunkowymi.
//

#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *perviousNode, *nextNode, *listValue;
	int value, childAmount;
};

struct Node *head;

void addNodeToMainList(struct Node *list, struct Node *input, int listIndex);
void deleteNodeMainList(struct Node *list, int listIndex);
void deleteChildren(struct Node *list);
struct Node * nodeConstructor(int value);

void addNode(struct Node *list, int inputIndex, int listIndex, int elementIndex) {
	if (listIndex < 0)
		return;

	if (elementIndex == -1) {
		addNodeToMainList(list, nodeConstructor(inputIndex), listIndex);
		return;
	}

	if (listIndex > list->childAmount)
		return;

	struct Node *input = nodeConstructor(inputIndex);

	if (listIndex > 0) {
		for (int i = 0; i < listIndex; i++)
			list = list->nextNode;
	}

	if (elementIndex == 0) {
		if (list->listValue == NULL) {
			list->listValue = input;
			return;
		}

		input->nextNode = list->listValue;
		list->listValue->perviousNode = input;
		input->childAmount = list->listValue->childAmount + 1;
		list->listValue = input;
		return;
	}
	if (elementIndex > list->listValue->childAmount + 1)
		return;
	else {
		list = list->listValue;
		if (elementIndex == list->childAmount + 1) {
			while (1) {
				list->childAmount++;
				if (list->nextNode == NULL)
					break;
				list = list->nextNode;
			}
			input->perviousNode = list;
			list->nextNode = input;
			return;
		}
		else {
			for (int i = 0; i < elementIndex; i++) {
				list->childAmount++;
				list = list->nextNode;
			}
			input->nextNode = list->nextNode;
			input->perviousNode = list;
			input->childAmount = list->nextNode->childAmount + 1;
			list->nextNode->perviousNode = input;
			list->nextNode = input;
			return;
		}
	}
}

void addNodeToMainList(struct Node *list, struct Node *input, int listIndex) {
	if (listIndex > list->childAmount + 1)
		return;

	if (listIndex != list->childAmount + 1) {
		for (int i = 0; i < listIndex; i++) {
			list->childAmount++;
			list = list->nextNode;
		}
	}
	else {
		while (1) {
			list->childAmount++;
			if (list->nextNode == NULL)
				break;
			else
				list = list->nextNode;
		}
		list->nextNode = input;
		input->perviousNode = list;
		return;
	}


	if (list->perviousNode == NULL) {		// pierwszy element listy
		list->perviousNode = input;
		input->nextNode = list;
		input->childAmount = list->childAmount + 1;
		if (list == head)
			head = input;

		return;
	}
	else {									// inne elementy listy
		input->nextNode = list;
		input->perviousNode = list->perviousNode;
		input->childAmount = list->childAmount + 1;
		list->perviousNode->nextNode = input;
		list->perviousNode = input;
		return;
	}
}

void deleteNode(struct Node *list, int listIndex, int elementIndex) {
	if (listIndex < 0)
		return;

	if (listIndex > list->childAmount)
		return;

	if (elementIndex < 0) {
		deleteNodeMainList(list, listIndex);
		return;
	}

	if (listIndex > 0)
		for (int i = 0; i < listIndex; i++)
			list = list->nextNode;

	struct Node *copy = list;

	list = list->listValue;
	if (list == NULL)
		return;

	if (elementIndex > list->childAmount)
		return;

	if (elementIndex == 0) {
		if (elementIndex == list->childAmount) {
			copy->listValue = NULL;
			free(list);
		}
		else {
			copy->listValue = list->nextNode;
			copy->listValue->perviousNode = NULL;
			free(list);
		}
		return;
	}

	if (elementIndex == list->childAmount) {
		while (1) {
			if (list->nextNode == NULL)
				break;
			list->childAmount--;
			list = list->nextNode;
		}

		list->perviousNode->nextNode = NULL;
		return;
	}

	else {
		for (int i = 0; i < elementIndex; i++) {
			list->childAmount--;
			list = list->nextNode;
		}

		list->perviousNode->nextNode = list->nextNode;
		list->nextNode->perviousNode = list->perviousNode;
		free(list);
		return;
	}

}

void deleteNodeMainList(struct Node *list, int listIndex) {
	if (listIndex > list->childAmount)
		return;

	if (listIndex == 0) {
		head = head->nextNode;
		head->perviousNode = NULL;
		deleteChildren(list);
		free(list);
		return;
	}

	if (listIndex == list->childAmount) {
		while (1) {
			list->childAmount--;
			if (list->nextNode == NULL)
				break;

			list = list->nextNode;

		}
		list->perviousNode->nextNode = NULL;
		deleteChildren(list);
		free(list);
		return;
	}
	else {
		for (int i = 0; i < listIndex; i++) {
			list->childAmount--;
			list = list->nextNode;
		}

		list->perviousNode->nextNode = list->nextNode;
		list->nextNode->perviousNode = list->perviousNode;
		deleteChildren(list);
		free(list);
		return;
	}
}

void deleteChildren(struct Node *list) {
	struct Node *forDelete;
	if (list->listValue != NULL) {
		list = list->listValue;
		while (1) {
			forDelete = list;
			list = list->nextNode;
			free(forDelete);
			if (list == NULL)
				break;
		}
	}
}

void changeValue(struct Node *list, int listIndex, int elementIndex, int value) {
	if (listIndex > list->childAmount)
		return;

	if (listIndex != 0) {
		changeValue(list->nextNode, listIndex - 1, elementIndex, value);
		return;
	}
	if (elementIndex == 0) {
		list->listValue->value = value;
		return;
	}
	if (elementIndex == -1) {
		list->value = value;
		return;
	}


	if (elementIndex > 0) {
		changeValue(list->listValue, elementIndex, -1, value);
		return;
	}


}

void print(struct Node *list) {
	system("cls");
	struct Node *tempList;
	int i = 0;
	while (1) {
		tempList = list->listValue;
		printf("Wartosc listy: %d numer listy %d:\n", list->value, i);
		if (tempList != NULL) {
			while (1) {
				printf("%d ", tempList->value);
				tempList = tempList->nextNode;
				if (tempList == NULL)
					break;
			}
			printf("\n");
		}
		else
			printf("empty\n");
		list = list->nextNode;
		i++;
		if (list == NULL)
			break;
	}
}

struct Node * nodeConstructor(int value) {
	struct Node *list = malloc(sizeof(struct Node));
	list->nextNode = NULL;
	list->perviousNode = NULL;
	list->listValue = NULL;
	list->value = value;
	list->childAmount = 0;
	return list;
}

int main() {
	head = nodeConstructor(0);
	char operation, sth;
	int mainListIndex, childListIndex, value;
	print(head);

	while (1) {
		scanf_s("%c ", &operation);

		if (operation == 'a') {
			scanf_s("%d %d %d", &mainListIndex, &childListIndex, &value);
			addNode(head, value, mainListIndex, childListIndex);
		}
		if (operation == 'd') {
			scanf_s("%d %d", &mainListIndex, &childListIndex);
			deleteNode(head, mainListIndex, childListIndex);
		}
		print(head);
	}

	addNode(head, 5, 0, -1);
	print(head);
	addNode(head, 2, 1, -1);
	print(head);
	addNode(head, 3, 2, -1);
	print(head);
	addNode(head, 4, 5, -1);
	print(head);
	addNode(head, 4, 7, -1);
	print(head);
	addNode(head, 5, -1, -1);
	print(head);

	addNode(head, 5, 0, 0);
	print(head);
	addNode(head, 2, 0, 1);
	print(head);
	addNode(head, 3, 5, 0);
	print(head);
	addNode(head, 4, 5, 1);
	print(head);
	addNode(head, 4, 0, 5);
	print(head);
	addNode(head, 9, 0, 0);
	print(head);
	addNode(head, 8, 0, 0);
	print(head);

	changeValue(head, 5, 1, 100);
	print(head);
	changeValue(head, 5, 0, 654);
	print(head);
	changeValue(head, 0, -1, 100423);
	print(head);

	deleteNode(head, 0, 0);
	print(head);
	deleteNode(head, 0, 2);
	print(head);
	deleteNode(head, 1, -1);
	print(head);
	deleteNode(head, 4, 1);
	print(head);
	deleteNode(head, 4, -1);
	print(head);


	print(head);
	return 0;
}