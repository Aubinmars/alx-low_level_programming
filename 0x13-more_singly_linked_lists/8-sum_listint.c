#include "lists.h"

/**
 * sum_listint_recursive - Helper function to calculate the sum recursively
 * @head: pointer to the current node in the linked list
 *
 * Return: the sum of all data starting from the current node
 */
int sum_listint_recursive(listint_t *head)
{
	if (head == NULL)
		return (0);

	return (head->n + sum_listint_recursive(head->next));
}

/**
 * sum_listint - calculates the sum of all the data in a listint_t list
 * @head: first node in the linked list
 *
 * Return: resulting sum
 */
int sum_listint(listint_t *head)
{
	return (sum_listint_recursive(head));
}
