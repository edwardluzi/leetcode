import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class Solution
{
	public String minWindow(String s, String t)
	{
		Map<Character, Integer> counters = new HashMap<Character, Integer>();

		for (int index = 0; index < t.length(); index++)
		{
			char ch = t.charAt(index);
			int count = counters.containsKey(ch) ? counters.get(ch) : 0;
			counters.put(ch, count + 1);
		}

		DoublyLinkedList<Integer> letterList = new DoublyLinkedList<Integer>();
		Map<Character, LinkedList<LinkedListNode<Integer>>> lettersMap = new HashMap<Character, LinkedList<LinkedListNode<Integer>>>();

		int index = 0;

		for (; index < s.length() && letterList.getCount() < t.length(); index++)
		{
			char ch = s.charAt(index);

			if (counters.containsKey(ch))
			{
				update(counters, lettersMap, letterList, ch, index);
			}
		}

		if (letterList.getCount() < t.length())
		{
			return "";
		}

		String candidate = s.substring(letterList.getFirst().getData(), index);

		for (; index < s.length(); index++)
		{
			char ch = s.charAt(index);

			if (lettersMap.containsKey(ch))
			{
				update(counters, lettersMap, letterList, ch, index);

				if (index - letterList.getFirst().getData() + 1 < candidate.length())
				{
					candidate = s.substring(letterList.getFirst().getData(), index + 1);
				}
			}
		}

		return candidate;
	}

	private void update(Map<Character, Integer> counters,
			Map<Character, LinkedList<LinkedListNode<Integer>>> lettersMap, DoublyLinkedList<Integer> letterList,
			char ch, int index)
	{
		LinkedList<LinkedListNode<Integer>> charList = null;

		if (lettersMap.containsKey(ch))
		{
			charList = lettersMap.get(ch);
		}
		else
		{
			charList = new LinkedList<LinkedListNode<Integer>>();
			lettersMap.put(ch, charList);
		}

		LinkedListNode<Integer> newNode = letterList.create(index);

		charList.addLast(newNode);
		letterList.addLast(newNode);

		if (charList.size() > counters.get(ch))
		{
			LinkedListNode<Integer> removedNode = charList.removeFirst();
			letterList.remove(removedNode);
		}
	}

	public interface LinkedListNode<E>
	{
		E getData();
	}

	public class DoublyLinkedList<E>
	{
		private class Node implements LinkedListNode<E>
		{
			private E data = null;
			private Node previous = null;
			private Node next = null;

			public Node(E data)
			{
				this.data = data;
			}

			public E getData()
			{
				return this.data;
			}

			public Node getPrevious()
			{
				return this.previous;
			}

			public void setPrevious(Node previous)
			{
				this.previous = previous;
			}

			public Node getNext()
			{
				return this.next;
			}

			public void setNext(Node next)
			{
				this.next = next;
			}
		}

		private int count = 0;
		private Node head = null;
		private Node tail = null;

		public int getCount()
		{
			return this.count;
		}

		public LinkedListNode<E> create(E data)
		{
			return new Node(data);
		}

		public LinkedListNode<E> getFirst()
		{
			return this.head;
		}

		public void addLast(LinkedListNode<E> node)
		{
			Node nativeNode = Node.class.isInstance(node) ? (Node) node : null;

			if (nativeNode != null)
			{
				if (this.head == null)
				{
					this.head = this.tail = nativeNode;
				}
				else
				{
					this.tail.setNext(nativeNode);
					nativeNode.setPrevious(this.tail);
					this.tail = nativeNode;
				}

				this.count++;
			}
		}

		public void remove(LinkedListNode<E> node)
		{
			Node nativeNode = Node.class.isInstance(node) ? (Node) node : null;

			if (nativeNode != null)
			{
				if (nativeNode == this.head)
				{
					if (nativeNode == this.tail)
					{
						this.tail = this.head = null;
					}
					else
					{
						this.head = this.head.getNext();
						this.head.setPrevious(null);
					}
				}
				else if (nativeNode == tail)
				{
					this.tail = this.tail.getPrevious();
					this.tail.setNext(null);
				}
				else
				{
					nativeNode.getPrevious().setNext(nativeNode.getNext());
					nativeNode.getNext().setPrevious(nativeNode.getPrevious());
				}

				this.count--;
			}
		}
	}
}
