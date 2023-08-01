#include "lists.h"

/**
 * reverse_listint_recursive - Reverses a linked list recursively.
 * @head: Double pointer to the first node in the list.
 * @prev: Pointer to the previous node (initially set to NULL).
 *
 * Return: Pointer to the first node in the new list.
 */
listint_t *reverse_listint_recursive(listint_t **head, listint_t *prev)
{
	listint_t *next;

	if (*head == NULL)
		return (prev);

	next = (*head)->next;
	(*head)->next = prev;

	return (reverse_listint_recursive(&next, *head));
}

/**
 * reverse_listint - Reverses a linked list.
 * @head: Double pointer to the first node in the list.
 *
 * Return: Pointer to the first node in the new list.
 */
listint_t *reverse_listint(listint_t **head)
{
	return (reverse_listint_recursive(head, NULL));
}
