# Wiki Layer Ingestion Rules
- **Cleaning:** Strip technical junk, ads, and irrelevant formatting from files in `raw/`.
- **Format:** Convert everything into clean, readable Markdown.
- **Linking:** Always use bidirectional wiki links (`[[Page_Name]]`) to connect related concepts.
- **Metadata:** Include YAML frontmatter with tags, creation date, summary, and source file path.
- **Output:** Save all processed files directly into the `wiki/` directory.
