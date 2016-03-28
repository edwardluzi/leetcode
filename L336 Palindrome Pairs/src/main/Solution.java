import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.concurrent.atomic.AtomicInteger;

public class Solution
{
	private static AtomicInteger counter = new AtomicInteger(0);

	private Map<String, Boolean> wordCache = new HashMap<String, Boolean>();
	private Map<Integer, List<Integer>> treeCache = new HashMap<Integer, List<Integer>>();

	public class TrieNode
	{
		private int id;
		private Character letter;
		private boolean isWord;
		private int wordId;
		private TrieNode[] nexts;

		public TrieNode()
		{
			this.id = counter.getAndIncrement();
			this.letter = 0;
			this.isWord = false;
			this.wordId = 0;
			this.nexts = new TrieNode[26];
		}

		public boolean isWord()
		{
			return isWord;
		}

		public void setWord(boolean isWord)
		{
			this.isWord = isWord;
		}

		public int getWordId()
		{
			return wordId;
		}

		public void setWordId(int wordId)
		{
			this.wordId = wordId;
		}

		public int getId()
		{
			return id;
		}

		public TrieNode[] getNexts()
		{
			return nexts;
		}

		public Character getLetter()
		{
			return letter;
		}

		public void setLetter(Character letter)
		{
			this.letter = letter;
		}
	}

	public class TrieTree
	{
		private TrieNode rootNode = new TrieNode();

		public TrieNode getRootNode()
		{
			return rootNode;
		}

		public void create(String[] words)
		{
			int wordId = 0;

			for (String s : words)
			{
				insertNode(rootNode, s, wordId++);
			}
		}

		void insertNode(TrieNode rootNode, String s, int wordId)
		{
			TrieNode current = rootNode;

			for (int i = 0; i < s.length(); i++)
			{
				int index = s.charAt(i) - 'a';
				TrieNode next = current.getNexts()[index];

				if (next == null)
				{
					TrieNode newNode = new TrieNode();
					newNode.setLetter(s.charAt(i));
					current.nexts[index] = newNode;
					current = newNode;
				}
				else
				{
					current = next;
				}
			}

			current.setWord(true);
			current.setWordId(wordId);
		}
	}

	public List<List<Integer>> palindromePairs(String[] words)
	{
		List<List<Integer>> result = new ArrayList<List<Integer>>();

		TrieTree tree = new TrieTree();

		tree.create(words);

		for (int i = 0; i < words.length; i++)
		{
			TrieNode current = tree.getRootNode();
			String reversed = new StringBuilder(words[i]).reverse().toString();

			for (int index = 0; index < reversed.length(); index++)
			{
				if (current.isWord() && current.getWordId() != i && this.isPalindrome(reversed.substring(index)))
				{
					result.add(Arrays.asList(new Integer[] { current.getWordId(), i }));
				}

				TrieNode next = current.getNexts()[reversed.charAt(index) - 'a'];

				if (next != null)
				{
					current = next;
				}
				else
				{
					current = null;
					break;
				}
			}

			if (current != null)
			{
				List<Integer> list = testPalindrome(current);

				for (Integer l : list)
				{
					if (l != i)
					{
						result.add(Arrays.asList(new Integer[] { l, i }));
					}
				}
			}
		}

		return result;
	}

	private boolean isPalindrome(String word)
	{
		if (this.wordCache.containsKey(word))
		{
			return this.wordCache.get(word);
		}

		int i = 0;
		int j = word.length() - 1;

		while (i <= j)
		{
			if (word.charAt(i++) != word.charAt(j--))
			{
				this.wordCache.put(word, false);
				return false;
			}
		}

		this.wordCache.put(word, true);

		return true;
	}

	private List<Integer> testPalindrome(TrieNode current)
	{
		if (this.treeCache.containsKey(current.getId()))
		{
			return this.treeCache.get(current.getId());
		}

		Map<Integer, String> words = new HashMap<Integer, String>();

		for (TrieNode child : current.getNexts())
		{
			if (child != null)
			{
				collectWords(child, "", words);
			}
		}

		List<Integer> list = new ArrayList<Integer>();

		if (current.isWord())
		{
			list.add(current.getWordId());
		}

		for (Entry<Integer, String> entry : words.entrySet())
		{
			if (isPalindrome(entry.getValue()))
			{
				list.add(entry.getKey());
			}
		}

		this.treeCache.put(current.getId(), list);

		return list;
	}

	private void collectWords(TrieNode current, String word, Map<Integer, String> words)
	{
		word += current.getLetter().toString();

		if (current.isWord)
		{
			words.put(current.getWordId(), word);
		}

		for (TrieNode child : current.getNexts())
		{
			if (child != null)
			{
				collectWords(child, word, words);
			}
		}
	}
}
