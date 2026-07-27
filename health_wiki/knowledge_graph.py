import sqlite3
import json
import os

# Dynamically anchor the database path to this script's directory
DB_PATH = os.path.join(os.path.dirname(__file__), "workspace_graph.db")

def init_db():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS entities (
            id TEXT PRIMARY KEY,
            type TEXT,
            name TEXT,
            metadata TEXT
        )
    ''')
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS relations (
            source_id TEXT,
            target_id TEXT,
            relation_type TEXT,
            provenance TEXT
        )
    ''')
    conn.commit()
    conn.close()

def add_entity(entity_id, entity_type, name, metadata={}):
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute('INSERT OR REPLACE INTO entities (id, type, name, metadata) VALUES (?, ?, ?, ?)',
                   (entity_id, entity_type, name, json.dumps(metadata)))
    conn.commit()
    conn.close()

def add_relation(source_id, target_id, relation_type, provenance=""):
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute('INSERT INTO relations (source_id, target_id, relation_type, provenance) VALUES (?, ?, ?, ?)',
                   (source_id, target_id, relation_type, provenance))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    init_db()
    print("Knowledge graph initialized successfully in health_wiki path.")
