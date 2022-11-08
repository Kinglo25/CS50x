import csv
import sys


def main():

    file0 = open(sys.argv[1], "r")
    reader = csv.reader(file0)
    for row in reader:
        sub_seq = row[1:]
        break
    file0.close()

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    file1 = open(sys.argv[1], "r")
    database = csv.DictReader(file1)

    # TODO: Read DNA sequence file into a variable
    file2 = open(sys.argv[2], "r")
    seq = file2.read()
    # TODO: Find longest match of each STR in DNA sequence
    ans = {}
    for sub_seqs in sub_seq:
        ans[sub_seqs] = longest_match(seq, sub_seqs)
    # TODO: Check database for matching profiles
    for person in database:
        i = 0
        for sub_seqs in sub_seq:
            if ans[sub_seqs] == int(person[sub_seqs]):
                i += 1
                if i == len(sub_seq):
                    print(person["name"])
                    return
    print("No match")
    file1.close()
    file2.close()
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
