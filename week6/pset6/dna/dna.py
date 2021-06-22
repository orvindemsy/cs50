import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    dna_database = []

    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        # reader = csv.reader(file)

        # Populating dna database
        for data in reader:
            dna_database.append(data)

        # Getting the dna to be checked in the sequence
        dnas = reader.fieldnames[1:]

    # Reading dna sequence
    with open(sys.argv[2]) as file:
        sequence = file.readline().strip()

    # print(sequence)

    # Counting number of consecutive occurence of each dna in sequence
    dna_occur = {}
    for dna in dnas:
        occurence = count_dna(dna, sequence)
        dna_occur[dna] = max(occurence)

    # Find matching dna
    person = find_match(dna_occur, dna_database)
    print(person)


# === Helper functions ===
def find_match(dna_occurence, dna_database):
    # How many short dna sequence to be checked
    dna_num = len(dna_occurence.keys())

    # Iterate over each person inside dna_database
    for person in dna_database:
        match_num = 0

        # Checking the dna occurences in the sequence with current person
        for dna in dna_occurence:
            if (dna_occurence[dna] == int(person[dna])):
                match_num += 1

        # If all sequence match then return the person's name
        if match_num == dna_num:
            return person["name"]

    return "No match"


def count_dna(dna, sequence):
    # Keep track of occurence
    occurence = []

    # Iterate over all sub sequence, check for matching dna strip
    for i in range(len(sequence)-len(dna)):

        # Checking sequence with length dna
        curr_seq = sequence[i:i+len(dna)]
        # print(f"Looping current sequence: {curr_seq}")

        # If current sequence match with dna, check for consecutive occurence
        if (dna == curr_seq):

            # Initialize number of consecutive occurence
            count = 0

            # Count for consecutive occurence
            while (dna == curr_seq):
                count += 1
                # print(f"checking next sequence, consecutive occurence: {count}")
                curr_seq = sequence[i+len(dna)*(count): i+len(dna)*(count+1)]

            # Append number of consecutive occurence
            occurence.append(count)

    if not occurence:
        occurence = [0]

    return occurence


# Main
if __name__ == "__main__":
    main()