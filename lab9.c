#include <stdio.h>
#include<stdlib.h>
#define HASH_SIZE 23
// RecordType
struct RecordType
{
	int	id;
	char	name;
	int	order;
};
// Fill out this structure
struct HashType
{
	struct RecordType* record;
};

// Compute the hash function
int hash(int x)
{
	return x % HASH_SIZE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}
void insertIntoHash(struct HashType* hashTable, struct RecordType record)
{
    int index = hash(record.id);
    struct RecordType* newRecord = (struct RecordType*)malloc(sizeof(struct RecordType));
    if (newRecord == NULL)
    {
        printf("Cannot allocate memory for the new record\n");
        exit(-1);
    }
    *newRecord = record;
    hashTable[index].record = newRecord;
}
// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i = 0; i < hashSz; i++)
    {
        if (pHashArray[i].record != NULL)
        {
            printf("index %d -> %d, %c, %d\n", i, pHashArray[i].record->id, pHashArray[i].record->name, pHashArray[i].record->order);
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int i;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation
    struct HashType* pHashTable = (struct HashType*)malloc(sizeof(struct HashType) * HASH_SIZE);
    if (pHashTable == NULL)
    {
        printf("Cannot allocate memory for the hash table\n");
        exit(-1);
    }
    printf("HASH_SIZE: %d\n", HASH_SIZE);
    // Initialize the hash table
    for (i = 0; i < HASH_SIZE; ++i)
    {
        pHashTable[i].record = NULL;
    }

    // Insert records into the hash table
    for (i = 0; i < recordSz; ++i)
    {
        insertIntoHash(pHashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayInHash(pHashTable, HASH_SIZE);

    // Free allocated memory
    free(pRecords);

    free(pHashTable);
    return 0;
}
