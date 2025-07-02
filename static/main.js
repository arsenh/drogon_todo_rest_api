class TodoApp {
    constructor() {
        this.apiBase = 'http://localhost:8080';
        this.editingId = null;
        this.todos = [];

        this.initializeElements();
        this.bindEvents();
        this.loadTodos();
    }

    initializeElements() {
        this.form = document.getElementById('todo-form');
        this.titleInput = document.getElementById('title');
        this.descriptionInput = document.getElementById('description');
        this.cancelEditBtn = document.getElementById('cancel-edit');
        this.todosContainer = document.getElementById('todos-container');
        this.loadingDiv = document.getElementById('loading');
        this.alertContainer = document.getElementById('alert-container');
        this.todosCount = document.getElementById('todos-count');
        this.submitBtn = this.form.querySelector('button[type="submit"]');
    }

    bindEvents() {
        this.form.addEventListener('submit', (e) => this.handleSubmit(e));
        this.cancelEditBtn.addEventListener('click', () => this.cancelEdit());
    }

    async makeRequest(url, options = {}) {
        try {
            const response = await fetch(url, {
                headers: {
                    'Content-Type': 'application/json',
                    ...options.headers
                },
                ...options
            });

            const data = await response.json();

            if (!response.ok) {
                throw new Error(data.error || `HTTP error! status: ${response.status}`);
            }

            return data;
        } catch (error) {
            console.error('Request failed:', error);
            throw error;
        }
    }

    showAlert(message, type = 'error') {
        const alertDiv = document.createElement('div');
        alertDiv.className = `alert alert-${type}`;
        alertDiv.textContent = message;

        this.alertContainer.innerHTML = '';
        this.alertContainer.appendChild(alertDiv);

        setTimeout(() => {
            alertDiv.remove();
        }, 5000);
    }

    showLoading(show = true) {
        this.loadingDiv.classList.toggle('hidden', !show);
    }

    updateTodosCount() {
        const total = this.todos.length;
        const completed = this.todos.filter(todo => todo.completed).length;
        this.todosCount.textContent = `${total} todos (${completed} completed)`;
    }

    async loadTodos() {
        try {
            this.showLoading(true);
            const todos = await this.makeRequest(`${this.apiBase}/todos`);
            this.todos = Array.isArray(todos) ? todos : [];
            this.renderTodos();
        } catch (error) {
            this.showAlert(`Failed to load todos: ${error.message}`);
            this.todos = [];
            this.renderTodos();
        } finally {
            this.showLoading(false);
        }
    }

    renderTodos() {
        this.updateTodosCount();

        if (this.todos.length === 0) {
            this.todosContainer.innerHTML = `
                <div class="empty-state">
                    <div class="empty-state-icon">📝</div>
                    <h3>No todos yet</h3>
                    <p>Create your first todo to get started!</p>
                </div>
            `;
            return;
        }

        const todosHTML = this.todos.map(todo => this.createTodoHTML(todo)).join('');
        this.todosContainer.innerHTML = todosHTML;
    }

    createTodoHTML(todo) {
        const createdDate = new Date(todo.created_at).toLocaleString();
        const statusClass = todo.completed ? 'completed' : 'pending';
        const statusText = todo.completed ? 'Completed' : 'Pending';

        return `
            <div class="todo-item ${todo.completed ? 'completed' : ''}" data-id="${todo.id}">
                <div class="todo-header">
                    <div>
                        <div class="todo-title">${this.escapeHtml(todo.title)}</div>
                        <div class="todo-id">ID: ${todo.id}</div>
                    </div>
                </div>
                
                ${todo.description ? `<div class="todo-description">${this.escapeHtml(todo.description)}</div>` : ''}
                
                <div class="todo-meta">
                    <div class="todo-created">Created: ${createdDate}</div>
                    <div class="todo-status ${statusClass}">${statusText}</div>
                </div>
                
                <div class="todo-actions">
                    <button class="btn btn-primary" onclick="todoApp.editTodo(${todo.id})">Edit</button>
                    <button class="btn btn-${todo.completed ? 'secondary' : 'success'}" 
                            onclick="todoApp.toggleComplete(${todo.id})">
                        ${todo.completed ? 'Mark Pending' : 'Mark Complete'}
                    </button>
                    <button class="btn btn-danger" onclick="todoApp.deleteTodo(${todo.id})">Delete</button>
                </div>
            </div>
        `;
    }

    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }

    async handleSubmit(e) {
        e.preventDefault();

        const title = this.titleInput.value.trim();
        const description = this.descriptionInput.value.trim();

        if (!title) {
            this.showAlert('Title is required');
            return;
        }

        try {
            if (this.editingId) {
                await this.updateTodo(this.editingId, title, description);
            } else {
                await this.createTodo(title, description);
            }

            this.resetForm();
            await this.loadTodos();
        } catch (error) {
            this.showAlert(`Operation failed: ${error.message}`);
        }
    }

    async createTodo(title, description) {
        const todo = await this.makeRequest(`${this.apiBase}/todos`, {
            method: 'POST',
            body: JSON.stringify({ title, description })
        });

        this.showAlert('Todo created successfully!', 'success');
        return todo;
    }

    async updateTodo(id, title, description) {
        const todo = this.todos.find(t => t.id === id);
        if (!todo) throw new Error('Todo not found');

        const updateData = { title, description };

        const updatedTodo = await this.makeRequest(`${this.apiBase}/todos/${id}`, {
            method: 'PATCH',
            body: JSON.stringify(updateData)
        });

        this.showAlert('Todo updated successfully!', 'success');
        return updatedTodo;
    }

    async toggleComplete(id) {
        try {
            const todo = this.todos.find(t => t.id === id);
            if (!todo) throw new Error('Todo not found');

            await this.makeRequest(`${this.apiBase}/todos/${id}`, {
                method: 'PATCH',
                body: JSON.stringify({ completed: !todo.completed })
            });

            const action = !todo.completed ? 'completed' : 'marked as pending';
            this.showAlert(`Todo ${action} successfully!`, 'success');
            await this.loadTodos();
        } catch (error) {
            this.showAlert(`Failed to update todo: ${error.message}`);
        }
    }

    async deleteTodo(id) {
        if (!confirm('Are you sure you want to delete this todo?')) {
            return;
        }

        try {
            await this.makeRequest(`${this.apiBase}/todos/${id}`, {
                method: 'DELETE'
            });

            this.showAlert('Todo deleted successfully!', 'success');
            await this.loadTodos();
        } catch (error) {
            this.showAlert(`Failed to delete todo: ${error.message}`);
        }
    }

    editTodo(id) {
        const todo = this.todos.find(t => t.id === id);
        if (!todo) return;

        this.editingId = id;
        this.titleInput.value = todo.title;
        this.descriptionInput.value = todo.description || '';
        this.submitBtn.textContent = 'Update Todo';
        this.cancelEditBtn.classList.remove('hidden');

        this.titleInput.focus();
        this.form.scrollIntoView({ behavior: 'smooth' });
    }

    cancelEdit() {
        this.resetForm();
    }

    resetForm() {
        this.editingId = null;
        this.form.reset();
        this.submitBtn.textContent = 'Add Todo';
        this.cancelEditBtn.classList.add('hidden');
    }
}

// Initialize the app when DOM is loaded
let todoApp;
document.addEventListener('DOMContentLoaded', () => {
    todoApp = new TodoApp();
});