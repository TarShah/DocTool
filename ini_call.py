import openai
import sys
API_KEY = "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"
if __name__ == '__main__':
	if len(sys.argv) < 1:
		print("Usage: python3 script.py")
		sys.exit(1)

	with open("real_query.txt", 'r') as f:
		quer = f.read()

	openai.api_key = API_KEY
	'''Give the nouns and their corresponding synonyms in the given sentence '''
	'''prompt = "I would give you a query that I want to find the answer of in a book about Mahatma Gandhi. I expect you to give me nothing other than a numbered list of relevant  keywords that I will use to rank the top k paragraphs using a scoring function . I also don't need any starting introduction that you have given about the answer.  remove general words from it and give only query specific keywords. I need only a list of single words (not even phrases)  that I would write into a file and later read from it. Since I want to read from that file I only need the list and nothing other than that.The first line of the output should be the first element of the list and last line of the output should be last element of list. Remember that every element of the list is a single word and not even a phrase. Give me the best  keywords according to you.  I expect you to include hindi to english translations of the words in the given query  as SEPERATE (not in the same line) elements of the list.Don't include the words 'English','Hindi','Translations'. Now give me exactly what I expect for the query - " + quer'''
		
	prompt = "Give the nouns and their corresponding synonyms in the given sentence :" + quer
	query = {
	"role": "user",
	"content": prompt
	}
	chat = openai.ChatCompletion.create(
	model="gpt-3.5-turbo",
	messages=[query],
	)
	reply = chat.choices[0].message.content
	filename = "filtered_query.txt"
	quer = reply
	with open(filename, 'w') as f:
		f.write(reply)
