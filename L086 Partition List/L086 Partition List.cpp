#include "stdafx.h"

struct ListNode
{
	int val;
	ListNode *next;
	explicit ListNode(int x)
		:val(x), next(NULL)
	{
	}
};

class Solution
{
public:

	static ListNode* partition(ListNode* head, int x)
	{
		ListNode* smallHead = NULL;
		ListNode* smallLast = NULL;

		ListNode* current = head;
		ListNode* last = NULL;
		ListNode* next = NULL;

		while (current != NULL)
		{
			next = current->next;

			if (current->val < x)
			{
				remove(head, last, current);
				current->next = NULL;
				append(smallHead, smallLast, current);
			}
			else
			{
				last = current;
			}

			current = next;
		}

		current = head;
		append(smallHead, smallLast, current);

		return smallHead;
	}

private:

	static inline void remove(ListNode*& head, ListNode*& last, ListNode* current)
	{
		if (head == current)
		{
			head = current->next;
		}
		else
		{
			last->next = current->next;
		}
	}

	static inline void append(ListNode*& head, ListNode*& last, ListNode* node)
	{
		if (head == NULL)
		{
			head = last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}
	}
};

static ListNode* createListNode(int list[], int size)
{
	ListNode* head = NULL;
	ListNode* current = NULL;

	for (int index = 0; index < size; index++)
	{
		if (head == NULL)
		{
			head = new ListNode(list[index]);
			current = head;
		}
		else
		{
			current->next = new ListNode(list[index]);
			current = current->next;
		}
	}

	return head;
}

static void print(char* name, ListNode* head)
{
	if (name != NULL)
	{
		printf(("%s: "), name);
	}

	while (head != NULL)
	{
		printf(("%d"), head->val);

		head = head->next;

		if (head != NULL)
		{
			printf(("->"));
		}
	}

	printf(("\n"));
}

int _tmain(int argc, _TCHAR* argv[])
{
	int list[] = { 4, 1, 4, 3, 2, 5, 2 };

	ListNode* head = createListNode(list, sizeof(list) / sizeof(int));

	print("Original", head);

	ListNode* newHead = Solution::partition(head, 3);

	print("New     ", newHead);

	return 0;
}