#include "lists.h"

/**
 * add_nodeint - adds a new node at the beginning of a linked list
 * @head: pointer to the pointer to the first node in the list
 * @n: data to insert in the new node
 *
 * Return: pointer to the new node, or NULL if it fails
 */
listint_t *add_nodeint(listint_t **head, const int n)
{
	listint_t *new;

	new = malloc(sizeof(listint_t)); /* Allocating memory for the new node. */
	if (!new) /* Check if memory allocation failed. */
	{
		return (NULL);
	}

	new->n = n; /* Setting the value of the new node. */
	new->next = *head; /* Pointing the new node to the previous head. */
	*head = new; /* Setting the new node as the new head. */

	return (new);
}
