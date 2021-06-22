from cs50 import get_string


def main():
    text = get_string("Text: ")
    print(text)


    # Count number of letters, words, and sentences
    n_letters     = count_letters(text);
    n_words       = count_words(text);
    n_sentences   = count_sentences(text);

    # Displaying number of words, letters, sentences
    print(f"{n_letters} letter(s)")
    print(f"{n_words} word(s)")
    print(f"{n_sentences} sentences(s)")
    print()

    # Compute Coleman-Liau index
    index = count_index(n_letters, n_words, n_sentences);

    if index < 1:
        print("Before Grade 1")

    elif index >= 16:
        print("Grade 16+")

    else:
        print("Grade ", index)


def count_letters(text):
    count = 0;

    # Count only alphabetic character, no punctuation, exclamation mark, digits, etc.
    for c in text:
        if c.isalpha():
            count += 1

    return count


def count_words(text):
    count = 0;

    # One word is defined as a sequence of characters separated by a space
    for c in text:
        if (c == " "):
            count += 1

    return count + 1


def count_sentences(text):
    count = 0;

    # Character ., !, ? marks the end of a sentence
    for c in text:
        if (c == "." or c == "!" or c == "?"):
            count += 1

    return count


def count_index(num_letters, num_words, num_sentences):
    # Average number of letters and sentences per 100 words
    L = num_letters / num_words * 100
    S = num_sentences / num_words * 100

    # printf("L: %f\n", L);
    # printf("S: %f\n", S);

    index = round(0.0588 * L - 0.296 * S - 15.8)

    return index

if __name__ == "__main__":
    main()