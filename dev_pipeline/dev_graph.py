import sqlite3
import json
import os

DB_PATH = os.path.join(os.path.dirname(__file__), "dev_workspace.db")

def init_dev_db():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS code_entities (
            id TEXT PRIMARY KEY,
            language TEXT,
            module TEXT,
            snippet TEXT,
            metadata TEXT
        )
    ''')
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS code_relations (
            source_id TEXT,
            target_id TEXT,
            relation_type TEXT,
            provenance TEXT
        )
    ''')
    conn.commit()
    conn.close()

if __name__ == "__main__":
    init_dev_db()
    print("Dev Knowledge Graph initialized successfully.")
